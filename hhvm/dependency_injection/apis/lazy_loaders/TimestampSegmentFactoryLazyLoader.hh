<?hh // strict

class TimestampSegmentFactoryLazyLoader extends LazyLoader<TimestampSegmentFactory> {

  public function __construct(
    private LazyLoader<HRTimestampSerializer> $hrTimestampSerializerLazyLoader
  ) {}

  protected function make(): TimestampSegmentFactory {
    return new TimestampSegmentFactory(
      $this->hrTimestampSerializerLazyLoader->load()
    );
  }
}
