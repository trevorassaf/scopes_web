<?hh // strict

class UploadBasicVideoMethod {

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
    private BasicVideoPathFormatMethod $basicVideoPathFormatMethod
  ) {}

  public function upload(
    UnsignedInt $completed_order_id,
    UnsignedInt $scope_index,
    string $title,
    Time $video_duration,
    string $tmp_file_name,
    HttpUploadedFile $uploaded_file
  ): BasicVideo {
    // Log upload basic video method call
    $this->logger->info(
      "Uploading basic video for CompletedOrder (id="
        . $completed_order_id->getNumber() . ") and scope index "
        . $scope_index->getNumber()
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

    // Check that the completed order exists. NOTE: we can't perform this later
    // because we need the ConfirmedOrder->timeOrdered in order to fetch the
    // VideoUploadPolicy
    $fetch_completed_order_handle = $this->fetchCompletedOrderByIdQuery->fetch(
      $completed_order_id
    );

    $completed_order = $fetch_completed_order_handle
      ->getWaitHandle()
      ->join();

    if ($completed_order === null) {
      throw new NonextantObjectException(
        "CompletedOrder (id=" . $completed_order_id->getNumber() . ") not found!",
        ObjectType::COMPLETED_ORDER
      );
    }

    // Make sure that the user linked with this session owns this order
    $fetch_confirmed_order_handle = $this->fetchConfirmedOrderByIdQuery->fetch(
      $completed_order->getConfirmedOrderId()
    );

    $confirmed_order = $fetch_confirmed_order_handle
      ->getWaitHandle()
      ->join();

    if ($confirmed_order === null) {
      throw new NonextantObjectException(
        "ConfirmedOrder (id=" . $completed_order->getConfirmedOrderId()->getNumber()
        . ") not found!",
        ObjectType::CONFIRMED_ORDER
      );
    }

    // Validate file size
    $video_upload_policy_handle = $this->fetchVideoUploadPolicyQuery->fetch(
      $confirmed_order->getTimeOrdered()
    );

    $video_upload_policy = $video_upload_policy_handle
      ->getWaitHandle()
      ->join();

    $max_video_size = $video_upload_policy->getMaxBytes();

    if ($max_video_size->lessThan($uploaded_file->getSize())) {
      throw new InvalidFileUploadException(
        "Video file size (" . $uploaded_file->getSize()->getNumber() . ") exceeds max video size ("
        . $max_video_size->getNumber() 
      );
    }

    //// The file is valid! Transfer video to permanent storage. ////

    // Check to see if a BasicVideoSet is registered with this CompletedOrder,
    // If not, this is the first BasicVideo uploaded so insert a BasicVideoSet
    // and attatch the video to that.
    $fetch_video_set_handle = $this->fetchCompletedBasicVideoSetByCompletedOrderQuery->fetch(
      $completed_order_id 
    );  

    $video_set = $fetch_video_set_handle
      ->getWaitHandle()
      ->join();

    if ($video_set === null) {
      $insert_video_set_handle = $this->insertCompletedBasicVideoSetQuery->insert(
        ImmMap{
          $this->completedBasicVideoSetTable->getCompletedOrderIdKey() => $completed_order_id->getNumber(),
        }
      ); 

      $video_set = $insert_video_set_handle
        ->getWaitHandle()
        ->join();
    }

    // Insert basic video record
    $upload_time = $this->timestampBuilder->now();

    $insert_query_handle = $this->insertBasicVideoQuery->insert(
      ImmMap{
        $this->basicVideosTable->getCompletedBasicVideoSetIdKey() => $video_set->getId()->getNumber(),
        $this->basicVideosTable->getScopeIndexKey() => $scope_index->getNumber(),
        $this->basicVideosTable->getTitleKey() => $title,
        $this->basicVideosTable->getVideoDurationKey() => $this->timeSerializer->serialize($video_duration),
        $this->basicVideosTable->getMimeIdKey() => $mime_type->getId()->getNumber(),
        $this->basicVideosTable->getUploadTimeKey() => $this->timestampSerializer->serialize($upload_time),
        $this->basicVideosTable->getHasVideoKey() => true,
      }
    );  

    $basic_video = $insert_query_handle
      ->getWaitHandle()
      ->join();

    // Move the file to permanent storage  
    $destination_path = $this->basicVideoPathFormatMethod->make(
      $video_upload_policy->getBasicVideoStoragePath(),
      $basic_video->getId(),
      $mime_type->getFileExtension()
    ); 

    $upload_succeeded = move_uploaded_file(
      $uploaded_file->getTmpName(),
      $destination_path
    );

    if (!$upload_succeeded) {
      throw new InvalidFileUploadException(
        "Failed to move uploaded basic video file!"
      );
    }
    
    return $basic_video;
  }

  private function makeUploadedFileKey(UnsignedInt $video_index): string {
    return self::BASIC_VIDEO_UPLOAD_KEY . (string)$video_index->getNumber();
  }

  private function getFiles(): ?ImmMap<string, ImmMap<string, ImmVector<mixed>>> {
    // UNSAFE
    return $_FILES;
  }
}
