<?hh // strict

class TimestampOperatorLazyLoader extends LazyLoader<TimestampOperator> {
  
  public function __construct(
    private HRTimestampSerializerLazyLoader $timestampSerializerLoader
  ) {}

  protected function make(): TimestampOperator {
    return new TimestampOperator(
      $this->timestampSerializerLoader->load()
    );
  }
}
