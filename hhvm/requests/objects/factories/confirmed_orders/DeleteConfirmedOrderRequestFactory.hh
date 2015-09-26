<?hh // strict

class DeleteConfirmedOrderRequestFactory implements RequestFactory<DeleteConfirmedOrderRequest> {

  private RequestFieldFactory<UnsignedInt> $confirmedOrderIdFieldFactory;

  public function __construct() {
    // Create call label id field factory
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $this->confirmedOrderIdFieldFactory = $uint_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): DeleteConfirmedOrderRequest {
    $delete_confirmed_order_request_builder = new DeleteConfirmedOrderRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case DeleteConfirmedOrderRequest::CONFIRMED_ORDER_ID_KEY:
          $delete_confirmed_order_request_builder->setConfirmedOrderId(
            $this->confirmedOrderIdFieldFactory->make($key, $value)
          );
          break;
        default:
          throw new UnexpectedRequestFieldKeyException(__CLASS__, $key);
          break;
      }
    }
    return $delete_confirmed_order_request_builder->build();
  }
}
