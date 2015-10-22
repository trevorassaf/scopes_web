<?hh // strict

class VideoUploadPolicyModelFactoryLazyLoader extends LazyLoader<ModelFactory<VideoUploadPolicy>> {

  public function __construct(
    private LazyLoader<VideoUploadPolicyTable> $videoUploadPolicyTableLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLoader
  ) {}

  protected function make(): ModelFactory<VideoUploadPolicy> {
    return new VideoUploadPolicyFactory(
      $this->timestampSerializerLoader->load(),
      $this->videoUploadPolicyTableLoader->load()
    );
  }
}
