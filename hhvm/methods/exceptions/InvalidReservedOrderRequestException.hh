<?hh // strict

class InvalidReservedOrderRequestException extends MethodException {

  public function __construct() {
    parent::__construct("Reserve order request rejected b/c it's INVALID");
  }
}
