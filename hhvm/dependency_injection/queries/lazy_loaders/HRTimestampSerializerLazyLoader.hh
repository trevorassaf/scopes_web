<?hh // strict

class HRTimestampSerializerLazyLoader extends LazyLoader<HRTimestampSerializer> {

  public function __construct(
    private LazyLoader<HRDateSerializer> $dateSerializerLazyLoader,
    private LazyLoader<HRTimeSerializer> $timeSerializerLazyLoader
  ) {}
  protected function make(): HRTimestampSerializer {
    return new HRTimestampSerializer(
      $this->dateSerializerLazyLoader->load(),
      $this->timeSerializerLazyLoader->load()
    );
  }
}
