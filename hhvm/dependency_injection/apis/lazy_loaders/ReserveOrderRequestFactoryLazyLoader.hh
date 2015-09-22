<?hh // strict

class ReserveOrderRequestFactoryLazyLoader extends LazyLoader<ReserveOrderRequestFactory> {

  public function __construct(
    private TimestampSerializer $timestampSerializer
  ) {}

  protected function make(): ReserveOrderRequestFactory {
    $timestamp_field_factory_builder = new TimestampRequestFieldFactoryBuilder(
      $this->timestampSerializer
    );
    return new ReserveOrderRequestFactory(
      $timestamp_field_factory_builder
    );
  }
}
