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
    private FetchCompletedCompositeVideoByEditedVideoOrderQuery $fetchCompletedCompositeVideoOrderByEditedVideoOrderQuery,
    private CompositeVideoPathFormatMethod $compositeVideoPathFormatMethod
  ) {}

  public function upload(
    UnsignedInt $user_id,
    UnsignedInt $edited_order_id,
    Time $video_duration,
    private string $title,
    private string $description,
    HttpUploadedFile $uploaded_file
  ): CompositeVideo {
    // Log file upload
    $this->logger->info(
      "Uploading edited video set for EditedVideoOrder (id="
      . $edited_order_id->getNumber() . ")"
    );
    
    // Check for errors caught by hhvm rutime 
    if ($uploaded_file->getErrorCode()->getNumber() !== 0) {
      throw new InvalidFileUploadException(
        "PHP file upload error with code " . $uploaded_file->getErrorCode()->getNumber()
      );
    }
    
    // Validate mime type
    $mime_types_handle = $this->fetchVideoMimeTypesQuery->fetch();

    $mime_type_list = $mime_types_handle
      ->getWaitHandle()
      ->join();

    $mime_type = null;

    foreach ($mime_type_list as $mime) {
      if ($mime->getHttpApplicationMimeType() == $uploaded_file->getType()) {
        $mime_type = $mime;
        break;
      }
    }

    if ($mime_type === null) {
      throw new InvalidFileUploadException(
        "Invalid mime type: " . $uploaded_file->getType()
      );
    }

    // Verify that this EditedOrder exists!
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

    // Make sure order has been completed
    $fetch_completed_order_handle = $this->fetchCompletedOrderByConfirmedOrderQuery->fetch(
      $edited_order->getConfirmedOrderId()
    );

    $completed_order = $fetch_completed_order_handle
      ->getWaitHandle()
      ->join();

    if ($completed_order === null) {
      throw new NonextantObjectException(
        "CompletedOrder not found for ConfirmedOrder (id=" . $edited_order->getConfirmedOrderId()->getNumber() . ")!",
        ObjectType::COMPLETED_ORDER
      ); 
    }

    // Fetch video upload policy
    $fetch_confirmed_order_handle = $this->fetchConfirmedOrderByIdQuery->fetch(
      $edited_order->getConfirmedOrderId()
    );

    $confirmed_order = $fetch_confirmed_order_handle
      ->getWaitHandle()
      ->join();

    if ($confirmed_order === null) {
      throw new NonextantObjectException(
        "ConfirmedOrder (id=" . $edited_order->getConfirmedOrderId()->getNumber() . ") not found!",
        ObjectType::CONFIRMED_ORDER
      );
    }

    $fetch_video_upload_handle = $this->fetchVideoUploadPolicyQuery->fetch(
      $confirmed_order->getTimeOrdered()
    );

    $video_upload_policy = $fetch_video_upload_handle
      ->getWaitHandle()
      ->join();

    // Validate file size
    $max_video_size = $video_upload_policy->getMaxBytes();

    if ($max_video_size->lessThan($uploaded_file->getSize())) {
      throw new InvalidFileUploadException(
        "Video file size (" . $uploaded_file->getSize()->getNumber() . ") exceeds max video size ("
        . $max_video_size->getNumber() 
      );
    }

    // Check that another EditedVideo hasn't already been uploaded. We can
    // simplify this check by fetching only the CompletedEditedVideo record,
    // and not the EditedVideo record. 
    $fetch_completed_composite_video_handle = $this->fetchCompletedCompositeVideoOrderByEditedVideoOrderQuery->fetch(
      $edited_order_id
    ); 

    $completed_composite_video = $fetch_completed_composite_video_handle
      ->getWaitHandle()
      ->join();

    if ($completed_composite_video !== null) {
      throw new DuplicateObjectMethodException(
        "EditedVideo already uploaded for EditedVideoOrder (id=" . $edited_order_id->getNumber() . ")!",
        ObjectType::EDITED_VIDEO
      );
    }

    //// The file is valid! Transfer video to permanent storage. ////

    // Insert CompletedCompositeVideo record
    $upload_time = $this->timestampBuilder->now();

    $insert_completed_composite_video_query_handle = $this->insertCompletedCompositeVideoQuery->insert(
      ImmMap{
        $this->completedCompositeVideoTable->getEditedVideoOrderIdKey() => $edited_order_id,
        $this->completedCompositeVideoTable->getTimeCompletedKey() => $this->timestampSerializer->serialize(
          $upload_time  
        ),
      }
    );

    $completed_composite_video = $insert_completed_composite_video_query_handle
      ->getWaitHandle()
      ->join();

    // Insert CompositeVideo record
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

    // Move file to permanent storage
    $destination_path = $this->compositeVideoPathFormatMethod->make(
      $video_upload_policy->getCompositeVideoStoragePath(),
      $composite_video->getId(),
      $mime_type->getFileExtension()
    );   

    $upload_succeeded = move_uploaded_file(
      $uploaded_file->getTmpName(),
      $destination_path
    );

    if (!$upload_succeeded) {
      throw new InvalidFileUploadException(
        "Failed to move uploaded composite video file!"
      );
    }

    return $composite_video;
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
