<?hh // strict

class UploadBasicVideosMethod {

  const string FILE_EXTENSION_DELIMITER = ".";

  const string BASIC_VIDEO_UPLOAD_KEY = "basic_video_file";

  public function __construct(
    private FetchCompletedBasicVideoSetByCompletedOrderQuery $fetchCompletedBasicVideoSetByCompletedOrderQuery,
    private FetchByIdQuery<CompletedOrder> $fetchCompletedOrderByIdQuery,
    private FetchByIdQuery<ConfirmedOrder> $fetchConfirmedOrderByIdQuery,
    private InsertQuery<BasicVideo> $insertBasicVideoQuery,
    private InsertQuery<CompletedBasicVideoSet> $insertCompletedBasicVideoSetQuery,
    private DeleteByIdQuery $deleteByIdQuery,
    private FetchVideoUploadPolicyQuery $fetchVideoUploadPolicyQuery,
    private FetchVideoMimeTypesQuery $fetchVideoMimeTypesQuery,
    private CompletedBasicVideoSetTable $completedBasicVideoSetTable,
    private BasicVideosTable $basicVideosTable,
    private Logger $logger,
    private TimestampBuilder $timestampBuilder,
    private HRTimestampSerializer $timestampSerializer,
    private HRTimeSerializer $timeSerializer,
    private HttpUploadedFilesFetcher $uploadedFilesFetcher
  ) {}

  public function upload(
    UnsignedInt $user_agent_id,
    UnsignedInt $completed_order_id,
    ImmVector<CreateBasicVideoRequest> $create_basic_video_requests
  ): ImmVector<UnsignedInt> {
    // Log file upload
    $this->logger->info(
      "Uploading basic video set for CompletedOrder (id="
      . $completed_order_id->getNumber() . ")"
    );

    //// Make sure that this order has been marked completed
    // Fetch completed order
    $fetch_completed_order_handle = $this->fetchCompletedOrderByIdQuery->fetch(
      $completed_order_id
    );

    $completed_order = $fetch_completed_order_handle
      ->getWaitHandle()
      ->join();

    // Check that completed order exists
    if ($completed_order === null) {
      throw new NonextantObjectException(
        "CompletedOrder (id=" . $completed_order_id->getNumber() . ") not found!",
        ObjectType::COMPLETED_ORDER
      );
    }

    // Fetch confirmed order
    $fetch_confirmed_order_handle = $this->fetchConfirmedOrderByIdQuery->fetch(
      $completed_order->getConfirmedOrderId()
    );

    $confirmed_order = $fetch_confirmed_order_handle
      ->getWaitHandle()
      ->join();

    // Check that confirmed order exists
    if ($confirmed_order === null) {
      throw new NonextantObjectException(
        "ConfirmedOrder (id=" . $completed_order->getConfirmedOrderId()->getNumber()
        . ") not found!",
        ObjectType::CONFIRMED_ORDER
      );
    }

    // Make sure that the user linked with this session owns this order
    if (!$user_agent_id->equals($confirmed_order->getUserId())) {
      throw new InvalidFileUploadException(
        "User associated with this session (id=" . $user_agent_id->getNumber() 
        . ") does not own specified ConfirmedOrder (id=" . $confirmed_order->getId()->getNumber(). ")!"
      );  
    }


    // Register basic video set with db
    $upload_time = $this->timestampBuilder->now();

    $insert_basic_video_set_handle = $this->insertCompletedBasicVideoSetQuery->insert(
      ImmMap{
        $this->completedBasicVideoSetTable->getCompletedOrderIdKey() => $completed_order->getId()->getNumber(),
        $this->completedBasicVideoSetTable->getTimeCompletedKey() => $this->timestampSerializer->serialize($upload_time)
      }  
    );

    $basic_video_set = $insert_basic_video_set_handle
      ->getWaitHandle()
      ->join();

    //// Upload videos to file system and place into db
    // Load upload policy
    $video_upload_policy_handle = $this->fetchVideoUploadPolicyQuery->fetch(
      $upload_time
    );

    $video_upload_policy = $video_upload_policy_handle
      ->getWaitHandle()
      ->join();

    //// Validate transfered files, insert metadata to db, move file to storage dir
    $files = $this->uploadedFilesFetcher->fetch();

    // Fail if files not uploaded
    if ($files->isEmpty()) {
      $this->logger->info(
        "No video files found!"   
      );

      throw new InvalidFileUploadException("No video files found!");   
    }

    // Fail if we receive unexpected number of multipart/formdata file labels
    if ($files->count() !== 1) {
      $this->logger->info(
        "Expected 1 multipart/encoding-formdata categories, but received " . $files->count()
      );  

      throw new InvalidFileUploadException(
        "Expected 1 multipart/encoding-formdata categories, but received " . $files->count()
      );
    }

    // Fail if the top-level multipart/encoding-formdata file label is incorrectly named
    $basic_videos_param_key = $video_upload_policy->getWebFilesParamKey();

    if (!$files->containsKey($basic_videos_param_key)) {
      throw new InvalidFileUploadException(
        "Expected multipart/encoding-formdata category with name '" . $basic_videos_param_key . "', " .
        "but received name '" . $files->keys()[0] . "'"
      );
    }
    
    // Load approved mime types
    $mime_types_handle = $this->fetchVideoMimeTypesQuery->fetch();

    $mime_types = $mime_types_handle
      ->getWaitHandle()
      ->join();

    // Extract basic videos 
    $basic_uploaded_files = $files->at($basic_videos_param_key);

    // Iterate through files and validate
    $scopes_count = $confirmed_order->getScopesCount();
    $max_video_size = $video_upload_policy->getMaxBytes();

    foreach ($basic_uploaded_files as $file_name => $file) {
      // Check for errors caught by php
      if ($file->getErrorCode()->getNumber() !== 0) {
        $this->logger->info(
          "PHP file upload error with code " . $file->getErrorCode()->getNumber()
        );

        throw new InvalidFileUploadException(
          "PHP file upload error with code " . $file->getErrorCode()->getNumber()
        );
      }

      // Validate file size
      if ($file->getSize()->greaterThan($max_video_size)) {
        $this->logger->info(
          "File size (" . $file->getSize()->getNumber() . "bytes) exceeds maximum "
          . "allowed file size (" . $max_video_size->getNumber() . "bytes)"
        ); 

        throw new InvalidFileUploadException(
          "File size (" . $file->getSize()->getNumber() . "bytes) exceeds maximum "
          . "allowed file size (" . $max_video_size->getNumber() . "bytes)"
        );
      }

      // Validate mime type
      $finfo = finfo_open(FILEINFO_MIME_TYPE); 
      $mime = finfo_file($finfo, $file->getTmpName());
      finfo_close($finfo);

      if (!$mime_types->containsKey($mime)) {
        $this->logger->info("Invalid file mime type: " . $mime); 
        throw new InvalidFileUploadException("Invalid file mime type: " . $mime);
      }
    }

    /**
     * At this point, the files have been validated and are ready to be moved 
     * from temporary to permanent storage on the file system. 
     */
    $basic_video_id_list = Vector{};

    for ($i = 0; $i < $scopes_count->getNumber(); ++$i) {
      $basic_video_req = $create_basic_video_requests[$i];

      // Register this basic video file with the db. We will derive the video's
      // file-name from the record id
      $insert_query_handle = $this->insertBasicVideoQuery->insert(
        ImmMap{
          $this->basicVideosTable->getCompletedBasicVideoSetIdKey() => $completed_order->getId()->getNumber(),
          $this->basicVideosTable->getScopeIndexKey() => $i,
          $this->basicVideosTable->getTitleKey() => $basic_video_req->getTitle(),
          $this->basicVideosTable->getDescriptionKey() => $basic_video_req->getDescription(), 
          $this->basicVideosTable->getVideoDurationKey() => $this->timeSerializer->serialize($basic_video_req->getVideoDuration())
        }
      );  

      $basic_video = $insert_query_handle
        ->getWaitHandle()
        ->join();

      // Create target path
      $uploaded_file = $files[$basic_videos_param_key][$basic_video_req->getFileName()];

      $finfo = finfo_open(FILEINFO_MIME_TYPE); 
      $mime = finfo_file($finfo, $uploaded_file->getTmpName());
      finfo_close($finfo);

      $target_path = $video_upload_policy->getBasicVideoStoragePath() . DIRECTORY_SEPARATOR
          . (string)$basic_video->getId()->getNumber() . self::FILE_EXTENSION_DELIMITER . $mime;
      
      // Move the file from temp storage to permanent storage  
      // Validate mime type
      $upload_succeeded = move_uploaded_file(
        $uploaded_file->getTmpName(),
        $target_path 
      );

      if (!$upload_succeeded) {
        $this->logger->info(
          "Failed to move uploaded basic video file!"
        );

        throw new InvalidFileUploadException(
          "Failed to move uploaded basic video file!"
        );
      }

      // Prepare basic video id list
      $basic_video_id_list[] = $basic_video->getId();
    }

    return $basic_video_id_list->toImmVector();
  }

  private function makeUploadedFileKey(UnsignedInt $video_index): string {
    return self::BASIC_VIDEO_UPLOAD_KEY . (string)$video_index->getNumber();
  }

  private function getFiles(): ?ImmMap<string, ImmMap<string, ImmVector<mixed>>> {
    // UNSAFE
    return $_FILES;
  }
}
