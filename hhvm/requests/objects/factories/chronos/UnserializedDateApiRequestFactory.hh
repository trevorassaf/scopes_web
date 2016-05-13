<?hh // strict

class UnserializedDateApiRequestFactory implements RequestFactory<UnserializedDateApiRequest> {

  private RequestFieldFactory<UnsignedInt> $yearsFieldFactory;
  private RequestFieldFactory<UnsignedInt> $monthsFieldFactory;
  private RequestFieldFactory<UnsignedInt> $dateFieldFactory;

  public function __construct() {
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();

    $this->yearsFieldFactory = $uint_field_factory_builder->build();
    $this->monthsFieldFactory = $uint_field_factory_builder->build();
    $this->dateFieldFactory = $uint_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): UnserializedDateApiRequest {
    $request_builder = new UnserializedDateApiRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case UnserializedDateApiRequest::YEAR_KEY: 
          $request_builder->setYear(
            $this->yearsFieldFactory->make($key, $value)
          );
          break;
        case UnserializedDateApiRequest::MONTH_KEY: 
          $request_builder->setMonth(
            $this->monthsFieldFactory->make($key, $value)
          );
          break;
        case UnserializedDateApiRequest::DATE_KEY: 
          $request_builder->setDate(
            $this->dateFieldFactory->make($key, $value)
          );
          break;
      }
    }
    return $request_builder->build();
  }
}
