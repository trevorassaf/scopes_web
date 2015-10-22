<?hh // strict

class VideoMimeTypeFactory extends ConcreteModelFactory<VideoMimeType> {
  
  public function __construct(
    private VideoMimeTypesTable $videoMimeTypesTable
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): VideoMimeType {
    return new VideoMimeType(
      $id,
      (string)$params[$this->videoMimeTypesTable->getMimeTypeKey()]
    );
  }
}
