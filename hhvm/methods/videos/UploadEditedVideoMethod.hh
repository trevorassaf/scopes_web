<?hh // strict

class UploadEditedVideoMethod {

  const string FILE_EXTENSION_DELIMITER = ".";

  public function __construct(
    private FetchByIdQuery<EditedVideoOrder> $fetchEditedVideoOrderByIdQuery,
    private FetchByIdQuery<ConfirmedOrder> $fetchConfirmedOrderByIdQuery,
    private FetchCompletedOrderByConfirmedOrderQuery $fetchCompletedOrderByConfirmedOrderQuery,
    private FetchByIdQuery<CompositeVideo> $fetchCompositeVideoByIdQuery,
    private FetchVideoUploadPolicyQuery $fetchVideoUploadPolicyQuery,
    private InsertQuery<CompositeVideo> $insertCompositeVideoQuery,
    private InsertQuery<CompletedCompositeVideo> $insertCompletedCompositeVideoQuery,
    private DeleteByIdQuery $deleteByIdQuery,
    private FetchVideoMimeTypesQuery $fetchVideoMimeTypesQuery,
    private CompositeVideoTable $compositeVideoTable,
    private CompletedCompositeVideoTable $completedCompositeVideoTable,
    private Logger $logger,
    private TimestampBuilder $timestampBuilder,
    private HRTimestampSerializer $timestampSerializer,
    private HRTimeSerializer $timeSerializer,
    private HttpUploadedFilesFetcher $uploadedFilesFetcher
  ) {}

  public function upload(
    UnsignedInt $user_id,
    UnsignedInt $edited_order_id,
    Time $video_duration,
    private string $title,
    private string $description,
    Timestamp $expiration_time
  ): UnsignedInt {
    // Log file upload
    $this->logger->info(
      "Uploading edited video set for EditedVideoOrder (id="
      . $edited_order_id->getNumber() . ")"
    );

    //// Make sure that this order has been fulfilled
    // Fetch edited video
    $fetch_edited_order_handle_query = $this->fetchEditedVideoOrderByIdQuery->fetch(
      $edited_order_id
    );

    $edited_order = $fetch_edited_order_handle_query
      ->getWaitHandle()
      ->join();

    if ($edited_order === null) {
      throw new NonextantObjectException(
        "EditedVideoOrder (id=" . $edited_order_id->getNumber() . ") not found!",
        ObjectType::EDITED_VIDEO_ORDER
      );
    }

    // Fetch confirmed order
    $fetch_confirmed_order_handle_query = $this->fetchConfirmedOrderByIdQuery->fetch(
      $edited_order->getConfirmedOrderId()
    );

    $confirmed_order = $fetch_confirmed_order_handle_query
      ->getWaitHandle()
      ->join();
    
    if ($confirmed_order === null) {
      throw new NonextantObjectException(
        "ConfirmedOrder (id=" . $edited_order->getConfirmedOrderId()->getNumber() . ") not found!",
        ObjectType::CONFIRMED_ORDER
      );
    }

    // Make sure that the user linked with this session owns this order
    if (!$user_id->equals($confirmed_order->getUserId())) {
      throw new InvalidFileUploadException(
        "User associated with this session (id=" . $user_id->getNumber() 
        . ") does not own specified ConfirmedOrder (id=" . $confirmed_order->getId()->getNumber(). ")!"
      );  
    }

    // Fetch completed order
    $fetch_completed_order_handle = $this->fetchCompletedOrderByConfirmedOrderQuery->fetch(
      $confirmed_order->getId()
    );

    $completed_order = $fetch_completed_order_handle
      ->getWaitHandle()
      ->join();
    
    if ($completed_order === null) {
      throw new NonextantObjectException(
        "CompletedOrder does not exist for ConfirmedOrder (id=" . $confirmed_order->getId()->getNumber() . ") not found!",
        ObjectType::COMPLETED_ORDER
      );
    }
    
    //// Validate edited video upload 
    // Load upload policy
    $upload_time = $this->timestampBuilder->now();
    $video_upload_policy_handle = $this->fetchVideoUploadPolicyQuery->fetch(
      $upload_time
    );

    $video_upload_policy = $video_upload_policy_handle
      ->getWaitHandle()
      ->join();
    
    // Validate transfered files, insert metadata to db, move file to storage directory
    $files = $this->uploadedFilesFetcher->fetch();

    // Fail if files not uploaded
    if ($files->isEmpty()) {
      throw new InvalidFileUploadException("No video files found!");   
    }

    // Fail if we receive unexpected number of multipart/formdata file labels
    if ($files->count() !== 1) {
      throw new InvalidFileUploadException(
        "Expected 1 multipart/encoding-formdata categories, but received " . $files->count()
      );
    }

    // Fail if the top-level multipart/encoding-formdata file label is incorrectly named
    $edited_videos_param_key = $video_upload_policy->getWebFilesParamKey();

    if (!$files->containsKey($edited_videos_param_key)) {
      throw new InvalidFileUploadException(
        "Expected multipart/encoding-formdata category with name '" . $edited_videos_param_key . "', " .
        "but received name '" . $files->keys()[0] . "'"
      );
    }

    // Validate php file upload 
    $composite_uploaded_file = $files->at($edited_videos_param_key);
    $file = $composite_uploaded_file->toImmVector()[0];

    if ($file->getErrorCode()->getNumber() !== 0) {
      throw new InvalidFileUploadException(
        "PHP file upload error with code " . $file->getErrorCode()->getNumber()
      );
    }

    // Validate file size
    $max_video_size = $video_upload_policy->getMaxBytes();

    if ($file->getSize()->greaterThan($max_video_size)) {
      throw new InvalidFileUploadException(
        "File size (" . $file->getSize()->getNumber() . "bytes) exceeds maximum "
        . "allowed file size (" . $max_video_size->getNumber() . "bytes)"
      );
    }

    // Validate mime type
    $mime_types_handle = $this->fetchVideoMimeTypesQuery->fetch();

    $mime_types = $mime_types_handle
      ->getWaitHandle()
      ->join();

    $finfo = finfo_open(FILEINFO_MIME_TYPE); 
    $mime = strtolower(finfo_file($finfo, $file->getTmpName()));
    finfo_close($finfo);

    if (!$mime_types->containsKey($mime)) {
      $this->logger->info("Invalid file mime type: " . $mime); 
      throw new InvalidFileUploadException("Invalid file mime type: " . $mime);
    }

    //// Insert records into db and transfer files to permanent storage 
    // Mark composite video as completed in db
    $insert_completed_composite_video_query_handle = $this->insertCompletedCompositeVideoQuery->insert(
      ImmMap{
        $this->completedCompositeVideoTable->getEditedVideoOrderIdKey() => $edited_order_id,
        $this->completedCompositeVideoTable->getTimeCompletedKey() => $this->timestampSerializer->serialize(
          $upload_time  
        ),
        $this->completedCompositeVideoTable->getExpirationTimeKey() => $this->timestampSerializer->serialize(
          $expiration_time  
        )
      }
    );

    $completed_composite_video = $insert_completed_composite_video_query_handle
      ->getWaitHandle()
      ->join();

    try {
      // Register this edited video with the db.
      $insert_query_handle = $this->insertCompositeVideoQuery->insert(
        ImmMap{
          $this->compositeVideoTable->getTitleKey() => $title,
          $this->compositeVideoTable->getDescriptionKey() => $description, 
          $this->compositeVideoTable->getDurationKey() => $this->timeSerializer->serialize($video_duration)
        }
      );

      $composite_video = $insert_query_handle
        ->getWaitHandle()
        ->join();

      //// Move video file to permanent storage
      // Create target path
      $target_path = $video_upload_policy->getCompositeVideoStoragePath() . DIRECTORY_SEPARATOR
        . (string)$composite_video->getId()->getNumber() . self::FILE_EXTENSION_DELIMITER . $mime;

      $upload_succeeded = move_uploaded_file(
        $file->getTmpName(),
        $target_path
      );

      if (!$upload_succeeded) {
        $delete_handle = $this->deleteByIdQuery->delete(
          $this->compositeVideoTable,
          $composite_video->getId()
        ); 

        $delete_handle
          ->getWaitHandle()
          ->join();

        $this->deleteCompletedCompositeVideo($completed_composite_video->getId());

        throw new InvalidFileUploadException(
          "Failed to transfer uploaded composite video file to permanent storage"
        );
      }

      return $composite_video->getId();
    } catch (QueryException $ex) {
      $this->deleteCompletedCompositeVideo($completed_composite_video->getId());
      throw $ex;
    }
  }

  private function deleteCompletedCompositeVideo(UnsignedInt $id): void {
    $delete_handle = $this->deleteByIdQuery->delete(
      $this->completedCompositeVideoTable,
      $id
    ); 

    $delete_handle
      ->getWaitHandle()
      ->join();
  }
}
