<?hh // strict

class UploadEditedVideoApiRequestFactoryLazyLoader extends LazyLoader<UploadEditedVideoApiRequestFactory> {

  public function __construct(
    private LazyLoader<TimestampRequestFieldFactoryBuilder> $timestampRequestFieldFactoryBuilderLazyLoader,
    private LazyLoader<TimeRequestFieldFactoryBuilder> $timeRequestFieldFactoryBuilderLazyLoader
  ) {}

  protected function make(): UploadEditedVideoApiRequestFactory {
    return new UploadEditedVideoApiRequestFactory(
      $this->timestampRequestFieldFactoryBuilderLazyLoader->load(),
      $this->timeRequestFieldFactoryBuilderLazyLoader->load() 
    );
  }
}
