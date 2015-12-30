<?hh // strict

class RequestFieldTypeConversionException extends RequestException {

  private static ImmMap<RequestFieldType, string> $REQUEST_FIELD_STRING_MAP = ImmMap{
    RequestFieldType::INT => "Int",
    RequestFieldType::UNSIGNED_INT => "Unsigned int",
    RequestFieldType::BOOL => "Bool",
    RequestFieldType::FLOAT => "Float",
    RequestFieldType::STRING => "String",
    RequestFieldType::EMAIL => "Email",
    RequestFieldType::TIMESTAMP => "Timestamp",
    RequestFieldType::TIME => "Time",
  };

  public function __construct(
    private RequestFieldType $requestFieldType,
    private string $key,
    private mixed $value
  ) {
    parent::__construct(
      "Failed to convert <{$key}:".(string)$value."> to type: "
          . self::$REQUEST_FIELD_STRING_MAP[$this->requestFieldType]
    );
  }
}
