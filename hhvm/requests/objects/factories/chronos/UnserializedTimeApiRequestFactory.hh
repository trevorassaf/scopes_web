<?hh // strict

class UnserializedTimeApiRequestFactory implements RequestFactory<UnserializedTimeApiRequest> {

  private RequestFieldFactory<UnsignedInt> $hoursFieldFactory;
  private RequestFieldFactory<UnsignedInt> $minutesFieldFactory;
  private RequestFieldFactory<UnsignedInt> $secondsFieldFactory;

  public function __construct() {
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();

    $this->hoursFieldFactory = $uint_field_factory_builder->build();
    $this->minutesFieldFactory = $uint_field_factory_builder->build();
    $this->secondsFieldFactory = $uint_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): UnserializedTimeApiRequest {
    $request_builder = new UnserializedTimeApiRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case UnserializedTimeApiRequest::HOURS_KEY: 
          $request_builder->setHours(
            $this->hoursFieldFactory->make($key, $value)
          );
          break;
        case UnserializedTimeApiRequest::MINUTES_KEY: 
          $request_builder->setMinutes(
            $this->minutesFieldFactory->make($key, $value)
          );
          break;
        case UnserializedTimeApiRequest::SECONDS_KEY: 
          $request_builder->setSeconds(
            $this->secondsFieldFactory->make($key, $value)
          );
          break;
      }
    }
    return $request_builder->build();
  }


}
