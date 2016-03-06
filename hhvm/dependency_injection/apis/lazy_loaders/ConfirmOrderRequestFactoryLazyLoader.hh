<?hh // strict

class ConfirmOrderApiRequestFactoryLazyLoader extends LazyLoader<ConfirmOrderApiRequestFactory> {

  public function __construct(
    private TimestampSerializer $timestampSerializer
  ) {}

  protected function make(): ConfirmOrderApiRequestFactory {
    $timestamp_field_factory_builder = new TimestampRequestFieldFactoryBuilder(
      $this->timestampSerializer
    );

    return new ConfirmOrderApiRequestFactory(
      $timestamp_field_factory_builder
    );    
  }
}
