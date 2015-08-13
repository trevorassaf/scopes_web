<?hh // strict

class ApiException extends Exception {

  public function __construct(
    string $error_message      
  ) {
    parent::__construct($error_message);
  }
}
