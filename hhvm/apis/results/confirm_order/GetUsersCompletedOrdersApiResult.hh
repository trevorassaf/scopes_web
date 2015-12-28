<?hh // strict

class GetUsersCompletedOrdersApiResult extends SuccessfulApiResult {

  const string COMPLETED_ORDERS_KEY = "orders";

  public function __construct(
    private ImmVector<CompletedOrderApiObject> $completedOrderApiObject
  ) {
    parent::__construct(ApiType::GET_USERS_COMPLETED_ORDERS);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    $field_map_list = Vector{};
    foreach ($this->completedOrderApiObject as $order) {
      $field_map_list[] = $order->getResultFields();
    }
    return ImmMap{
      self::COMPLETED_ORDERS_KEY => $field_map_list->toImmVector(),
    };
  }
}
