<?hh // strict

class GetUsersConfirmedOrdersRequestFactory implements RequestFactory<GetUsersConfirmedOrdersRequest> {

  private RequestFieldFactory<UnsignedInt> $userIdFieldFactory;

  public function __construct() {
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $this->userIdFieldFactory = $uint_field_factory_builder->build(); 
  }

  public function make(ImmMap<string, mixed> $raw_field_map): GetUsersConfirmedOrdersRequest {
    $request_builder = new GetUsersConfirmedOrdersRequestBuilder();    
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case GetUsersConfirmedOrdersRequest::USER_ID_KEY:
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
