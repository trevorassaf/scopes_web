<?hh // strict

class GetUsersReservedOrdersApiRequestFactory implements RequestFactory<GetUsersReservedOrdersApiRequest> {

  private RequestFieldFactory<UnsignedInt>  $userIdFieldFactory;

  public function __construct() {
    // Create reserved order id field factory
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $this->userIdFieldFactory = $uint_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): GetUsersReservedOrdersApiRequest {
    $request_builder = new GetUsersReservedOrdersApiRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case GetUsersReservedOrdersApiRequest::USER_ID_KEY:
          $request_builder->setUserId(
            $this->userIdFieldFactory->make($key, $value)
          );
          break;
        default:
          throw new UnexpectedRequestFieldKeyException(__CLASS__, $key);
          break;
      }
    }
    return $request_builder->build();
  }
}
