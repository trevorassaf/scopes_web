<?hh // strict

class DuplicateUniqueKeyQueryException extends QueryException {

  public function __construct(
    string $error_code
  ) {
    parent::__construct(
      QueryErrorType::DUPLICATE_KEY,
      $error_code
    );
  }
}
