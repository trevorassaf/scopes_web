<?hh // strict

class CompleteOrderRequestFactory implements RequestFactory<CompleteOrderApiRequest> {
  
  private RequestFieldFactory<UnsignedInt> $confirmedOrderIdFieldFactory;

  public function __construct() {
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();

    $this->confirmedOrderIdFieldFactory = $uint_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): CompleteOrderApiRequest {
    $complete_order_request_builder = new CompleteOrderApiRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case CompleteOrderApiRequest::CONFIRMED_ORDER_ID_KEY:
          $complete_order_request_builder->setConfirmedOrderId(
            $this->confirmedOrderIdFieldFactory->make($key, $value)
          );
          break;
      } 
    }
    return $complete_order_request_builder->build();
  }

}
