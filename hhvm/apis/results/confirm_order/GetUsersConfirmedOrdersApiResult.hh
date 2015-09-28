<?hh // strict

class GetUsersConfirmedOrdersApiResult extends SuccessfulApiResult {

  public function __construct(
    public array<ConfirmOrderWithCellLabelResultStruct> $orders
  ) {
    parent::__construct(ApiType::GET_USERS_CONFIRMED_ORDERS);
  }
}
