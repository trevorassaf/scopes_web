<?hh // strict

class GetUsersConfirmedOrdersApiResult extends SuccessfulApiResult {

  // Top level result key
  const string CONFIRMED_ORDERS_LIST_KEY = "orders";

  public function __construct(
    private ImmVector<ConfirmOrderApiObject> $orders
  ) {
    parent::__construct(ApiType::GET_USERS_CONFIRMED_ORDERS);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    $raw_fields_vector = Vector{};
    
    foreach ($this->orders as $order) {
      $raw_fields_vector[] = $order->getResultFields();
    }

    return ImmMap{
      self::CONFIRMED_ORDERS_LIST_KEY => $raw_fields_vector->toImmVector(),
    };
  }
}
