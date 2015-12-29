<?hh // strict

class FailedDeserializationException extends Exception {

  public function __construct(string $param_string) {
    parent::__construct($param_string);
  }
}
