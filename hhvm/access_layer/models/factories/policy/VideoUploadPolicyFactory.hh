<?hh // strict

class VideoUploadPolicyFactory extends ConcreteModelFactory<VideoUploadPolicy> {

  public function __construct(
    private HRTimestampSerializer $timestampSerializer,
    private VideoUploadPolicyTable $videoUploadPolicyTable
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $param_map
  ): VideoUploadPolicy {
    return new VideoUploadPolicy(
      $id,
      new UnsignedInt((int)$param_map[$this->videoUploadPolicyTable->getMaxBytesKey()]),
      (string)$param_map[$this->videoUploadPolicyTable->getWebFilesParamKey()],
      (string)$param_map[$this->videoUploadPolicyTable->getBasicVideoStoragePathKey()],
      (string)$param_map[$this->videoUploadPolicyTable->getEditedVideoStoragePathKey()],
      $this->timestampSerializer->deserialize($this->videoUploadPolicyTable->getTimeEnactedKey())
    );
  }
}
