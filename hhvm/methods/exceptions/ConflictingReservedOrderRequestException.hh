<?hh // strict

class ConflictingReservedOrderRequestException extends MethodException {

  public function __construct() {
    parent::__construct("Reserve order request rejected b/c it CONFLICTS with existing orders");
  }
}
