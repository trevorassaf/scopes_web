<?hh // strict

class GetUsersReservedOrdersApiResult extends SuccessfulApiResult {

  const string RSVD_ORDERS_KEY = "rsvd-orders";

  public function __construct(
    private ImmVector<RsvdOrder> $reservedOrders
  ) {
    parent::__construct(ApiType::GET_USERS_RSVD_ORDERS);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::RSVD_ORDERS_KEY => $this->reservedOrders->toArray(),
    };  
  }
}
