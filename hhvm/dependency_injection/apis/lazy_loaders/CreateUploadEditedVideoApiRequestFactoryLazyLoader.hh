<?hh // strict

class CreateUploadEditedVideoApiRequestFactoryLazyLoader extends LazyLoader<CreateUploadEditedVideoApiRequestFactory> {

  public function __construct(
    private LazyLoader<TimestampRequestFieldFactoryBuilder> $timestampRequestFieldFactoryBuilderLazyLoader,
    private LazyLoader<TimeRequestFieldFactoryBuilder> $timeRequestFieldFactoryBuilderLazyLoader
  ) {}

  protected function make(): CreateUploadEditedVideoApiRequestFactory {
    return new CreateUploadEditedVideoApiRequestFactory(
      $this->timestampRequestFieldFactoryBuilderLazyLoader->load(),
      $this->timeRequestFieldFactoryBuilderLazyLoader->load() 
    );
  }
}
