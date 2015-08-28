<?hh // strict

class RequestFieldConstraintException extends Exception {

  private static ImmMap<RequestFieldConstraintType, string> $REQUEST_FIELD_CONSTRAINT_TYPE_NAME_MAP = ImmMap{
    RequestFieldConstraintType::MIN_VALUE => "Minimum Value",
    RequestFieldConstraintType::MAX_VALUE => "Maximum Value",
    RequestFieldConstraintType::MIN_LENGTH => "Minimum Length",
    RequestFieldConstraintType::MAX_LENGTH => "Maximum Length",
  };

  public function __construct(
    private RequestFieldConstraintType $requestFieldConstraintType,
    private string $key,
    private string $value
  ) {
    parent::__construct(
      "Request field <{$this->key}:{$this->value}> violates the \""
          . self::$REQUEST_FIELD_CONSTRAIN_TYPE_NAME_MAP[$this->requestFieldConstraintType] . "\" constraint";
    );
  }

}
