<?hh // strict

class MakeVideoUploadPolicyMethod {

  public function __construct(
    private InsertVideoUploadPolicyQuery $insertVideoUploadPolicyQuery,
    private TimestampBuilder $timestampBuilder
  ) {}

  public function make(
    UnsignedInt $max_bytes,
    string $basic_video_storage_path,
    string $composite_video_storage_path,
    string $web_files_param_key
  ): void {
    $upload_time = $this->timestampBuilder->now();
    $insert_handle = $this->insertVideoUploadPolicyQuery->insert(
      $max_bytes,
      $basic_video_storage_path,
      $composite_video_storage_path,
      $web_files_param_key,
      $upload_time
    );

    $insert_handle->getWaitHandle()->join();
  }
}
