<?hh // strict

class CreateUploadBasicVideosApiRequestFactoryLazyLoader extends LazyLoader<RequestFactory<CreateUploadBasicVideosApiRequest>> {

  public function __construct(
    private LazyLoader<TimestampRequestFieldFactoryBuilder> $timestampRequestFieldFactoryBuilderLazyLoader,
    private LazyLoader<TimeRequestFieldFactoryBuilder> $timeRequestFieldFactoryBuilderLazyLoader,
    private LazyLoader<HRTimeSerializer> $timeSerializerLazyLoader
  ) {}

  protected function make(): CreateUploadBasicVideosApiRequestFactory {
    return new CreateUploadBasicVideosApiRequestFactory(
      $this->timestampRequestFieldFactoryBuilderLazyLoader->load(),
      $this->timeRequestFieldFactoryBuilderLazyLoader->load(),
      $this->timeSerializerLazyLoader->load()
    );
  }

}
