<?hh // strict

class TimeRequestFieldFactoryBuilderLazyLoader extends LazyLoader<TimeRequestFieldFactoryBuilder> {

  public function __construct(
    private LazyLoader<HRTimeSerializer> $timeSerializerLazyLoader
  ) {}

  protected function make(): TimeRequestFieldFactoryBuilder {
    return new TimeRequestFieldFactoryBuilder(
      $this->timeSerializerLazyLoader->load()
    );
  }
}
