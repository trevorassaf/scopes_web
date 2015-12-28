<?hh // strict

class GetUsersReservedOrdersApiResult extends SuccessfulApiResult {

  const string RSVD_ORDERS_KEY = "rsvd-orders";

  public function __construct(
    private ImmVector<ReservedOrderApiObject> $reservedOrders
  ) {
    parent::__construct(ApiType::GET_USERS_RSVD_ORDERS);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    $reserved_order_result_list = Vector{};
    foreach ($this->reservedOrders as $order) {
      $reserved_order_result_list[] = $order->getResultFields();
    }
    return ImmMap{
      self::RSVD_ORDERS_KEY => $reserved_order_result_list->toImmVector(),
    };  
  }
}
