<?hh // strict

class VideoUploadPolicyModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<VideoUploadPolicy>> {

  public function __construct(
    private LazyLoader<VideoUploadPolicyTable> $videoUploadPolicyTableLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLoader
  ) {}

  protected function make(): ConcreteModelFactory<VideoUploadPolicy> {
    return new VideoUploadPolicyFactory(
      $this->timestampSerializerLoader->load(),
      $this->videoUploadPolicyTableLoader->load()
    );
  }
}
