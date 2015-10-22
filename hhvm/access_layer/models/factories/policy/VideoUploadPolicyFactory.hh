<?hh // strict

class VideoUploadPolicyFactory implements ModelFactory<VideoUploadPolicy> {

  public function __construct(
    private HRTimestampSerializer $timestampSerializer,
    private VideoUploadPolicyTable $videoUploadPolicyTable
  ) {}

  public function extrude(
    ImmMap<string, mixed> $param_map
  ): VideoUploadPolicy {
    return new VideoUploadPolicy(
      new UnsignedInt((int)$param_map[$this->videoUploadPolicyTable->getMaxBytesKey()]),
      (string)$param_map[$this->videoUploadPolicyTable->getBasicVideoStoragePathKey()],
      (string)$param_map[$this->videoUploadPolicyTable->getEditedVideoStoragePathKey()],
      $this->timestampSerializer->deserialize($this->videoUploadPolicyTable->getTimeEnactedKey())
    );
  }
}
