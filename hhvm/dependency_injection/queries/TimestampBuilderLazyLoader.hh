<?hh // strict

class TimestampBuilderLazyLoader extends LazyLoader<TimestampBuilder> {

  public function __construct(
    private LazyLoader<TimestampSerializer> $timestampSerializerLoader
  ) {}

  protected function make(): TimestampBuilder {
    return new TimestampBuilder(
      $this->timestampSerializerLoader->load()
    );
  }
}
