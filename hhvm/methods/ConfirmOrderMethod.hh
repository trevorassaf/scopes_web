<?hh // strict

class ConfirmOrderMethod {

  public function __construct(
    private ConfirmedOrderInsertQuery $confirmedOrderInsertQuery
  ) {}

  public function confirm(
    ConfirmOrderRequest $confirm_order_request
  ): void {
    // 1. Fetch existing reserved order (ensure number
    //      of cell label requests matches scopes number)
    // 2. Insert new confirmed order
    // 3. Insert cell label requests
    // 4. Delete reserved order
    try {
      // Fetch reserved order       

    } catch (QueryException $ex) {} 
  }
}
