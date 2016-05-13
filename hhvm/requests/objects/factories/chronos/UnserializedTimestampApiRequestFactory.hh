<?hh // strict

class UnserializedTimestampApiRequestFactory implements RequestFactory<UnserializedTimestampApiRequest> {

  private UnserializedDateApiRequestFactory $dateFieldFactory;
  private UnserializedTimeApiRequestFactory $timeFieldFactory;
  private MapApiRequestFieldFactory<string, mixed> $mapFactory;

  public function __construct() {
    $this->dateFieldFactory = new UnserializedDateApiRequestFactory();
    $this->timeFieldFactory = new UnserializedTimeApiRequestFactory();

    $string_field_factory_builder = new StringRequestFieldFactoryBuilder();
    $mixed_field_factory_builder = new MixedRequestFieldFactoryBuilder();
    $this->mapFactory = new MapApiRequestFieldFactory(
      $string_field_factory_builder->build(),
      $mixed_field_factory_builder->build()
    );
  }

  public function make(ImmMap<string, mixed> $raw_field_map): UnserializedTimestampApiRequest {
    $request_builder = new UnserializedTimestampApiRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case UnserializedTimestampApiRequest::DATE_KEY:
          $map = $this->mapFactory->convert($key, $value);
          $request_builder->setDate(
            $this->dateFieldFactory->make($map->get())
          );
          break;
        case UnserializedTimestampApiRequest::TIME_KEY:
          $map = $this->mapFactory->convert($key, $value);
          $request_builder->setTime(
            $this->timeFieldFactory->make($map->get())
          );
          break;
      }
    }
    return $request_builder->build();
  }
}
