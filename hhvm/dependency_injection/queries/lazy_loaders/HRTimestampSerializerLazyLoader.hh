<?hh // strict

class HRTimestampSerializerLazyLoader extends LazyLoader<TimestampSerializer> {

  public function __construct(
    private LazyLoader<HRDateSerializer> $dateSerializerLazyLoader,
    private LazyLoader<HRTimeSerializer> $timeSerializerLazyLoader
  ) {}
  protected function make(): TimestampSerializer {
    return new HRTimestampSerializer(
      $this->dateSerializerLazyLoader->load(),
      $this->timeSerializerLazyLoader->load()
    );
  }
}
