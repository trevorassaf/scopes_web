<?hh // strict

class InsertVideoUploadPolicyQuery {
  
  public function __construct(
    private InsertQuery<VideoUploadPolicy> $insertQuery,
    private VideoUploadPolicyTable $videoUploadPolicyTable,
    private HRTimestampSerializer $hrTimestampSerializer
  ) {}

  public async function insert(
    UnsignedInt $max_bytes,
    string $basic_video_storage_path,
    string $composite_video_storage_path,
    string $web_files_param_key,
    Timestamp $time_enacted
  ): Awaitable<VideoUploadPolicy> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->videoUploadPolicyTable->getMaxBytesKey() => $max_bytes->getNumber(),
        $this->videoUploadPolicyTable->getBasicVideoStoragePathKey() => $basic_video_storage_path,
        $this->videoUploadPolicyTable->getEditedVideoStoragePathKey() => $composite_video_storage_path,
        $this->videoUploadPolicyTable->getWebFilesParamKey() => $web_files_param_key,
        $this->videoUploadPolicyTable->getTimeEnactedKey() => $this->hrTimestampSerializer->serialize($time_enacted),
      }
    ); 
  }
}
