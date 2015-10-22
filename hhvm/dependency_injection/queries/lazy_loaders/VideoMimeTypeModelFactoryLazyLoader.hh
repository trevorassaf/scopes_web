<?hh // strict

class VideoMimeTypeModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<VideoMimeType>> {

  public function __construct(
    private LazyLoader<VideoMimeTypesTable> $videoMimeTypesTableLoader
  ) {}

  protected function make(): ConcreteModelFactory<VideoMimeType> {
    return new VideoMimeTypeFactory(
      $this->videoMimeTypesTableLoader->load()
    );
  }
}
