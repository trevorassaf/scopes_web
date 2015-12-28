<?hh // strict

class GetUsersCompletedOrdersApiRequestFactory implements RequestFactory<GetUsersCompletedOrdersApiRequest> {

  private RequestFieldFactory<UnsignedInt> $userIdFieldFactory;

  public function __construct() {
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $this->userIdFieldFactory = $uint_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): GetUsersCompletedOrdersApiRequest {
    $request_builder = new GetUsersCompletedOrdersApiRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case GetUsersCompletedOrdersApiRequest::USER_ID_KEY:
          $request_builder->setUserId(
            $this->userIdFieldFactory->make($key, $value)
          );
          break;
      }
    } 
    return $request_builder->build();
  }
}
