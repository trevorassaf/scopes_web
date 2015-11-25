<?hh // strict

class TimestampRequestFieldFactoryBuilderLazyLoader extends LazyLoader<TimestampRequestFieldFactoryBuilder> {

  public function __construct(
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLazyLoader
  ) {}
  
  protected function make(): TimestampRequestFieldFactoryBuilder {
    return new TimestampRequestFieldFactoryBuilder(
      $this->timestampSerializerLazyLoader->load()
    );    
  }
}
