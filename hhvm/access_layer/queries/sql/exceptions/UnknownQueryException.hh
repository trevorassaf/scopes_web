<?hh // strict

class UnknownQueryException extends QueryException {

  public function __construct(
    string $error_code
  ) {
    parent::__construct(
      QueryErrorType::UNKNOWN,
      $error_code
    );
  }
}
