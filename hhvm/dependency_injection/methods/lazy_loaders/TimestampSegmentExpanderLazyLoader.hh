<?hh // strict

class TimestampSegmentExpanderLazyLoader extends LazyLoader<TimestampSegmentExpander> {

  public function __construct(
    private LazyLoader<HRDateSerializer> $hrDateSerializerLoader
  ) {}

  protected function make(): TimestampSegmentExpander {
    return new TimestampSegmentExpander(
      $this->hrDateSerializerLoader->load() 
    );
  }
}
