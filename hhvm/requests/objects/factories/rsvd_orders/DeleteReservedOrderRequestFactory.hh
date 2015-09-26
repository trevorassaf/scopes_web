<?hh // strict

class DeleteReservedOrderRequestFactory implements RequestFactory<DeleteReservedOrderRequest> {
  
  private RequestFieldFactory<UnsignedInt> $reserveOrderIdFieldFactory;

  public function __construct() {
    // Create call label id field factory
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $this->reserveOrderIdFieldFactory = $uint_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): DeleteReservedOrderRequest {
    $delete_rsvd_order_request_builder = new DeleteReservedOrderRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case DeleteReservedOrderRequest::RSVD_ORDER_ID_KEY:
          $delete_rsvd_order_request_builder->setReservedOrderId(
            $this->reserveOrderIdFieldFactory->make($key, $value)
          );
          break;
        default:
          throw new UnexpectedRequestFieldKeyException(__CLASS__, $key);
          break;
      }
    }
    return $delete_rsvd_order_request_builder->build();
  }
}
