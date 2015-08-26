<?hh // strict

class RequestMapper<Trequest> {

  public function __construct(
    private RequestBuilderFactory<Trequest> $requestBuilderFactory
  ) {}

  public function map(ImmMap<string, mixed> $request_fields): Trequest {
    $request_builder = $this->requestBuilderFactory->get();
    foreach ($request_fields as $key => $value) {
      $request_builder->bind($key, $value);
    }
    return $request_builder->build();
  }
}
