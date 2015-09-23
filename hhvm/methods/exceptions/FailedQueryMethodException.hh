<?hh // strict

class FailedQueryMethodException extends MethodException {

  public function __construct(
    private QueryException $ex
  ) {
    parent::__construct($ex->getMessage());
  }
}
