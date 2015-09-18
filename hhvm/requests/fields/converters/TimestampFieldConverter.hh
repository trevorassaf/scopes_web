<?hh // strict

class TimestampFieldConverter implements RequestFieldTypeConverter<Timestamp> {

  public function __construct(
    private TimestampSerializer $timestampSerializer
  ) {}

  public function convert(string $key, mixed $value): Timestamp {
    // Validate int type
    if (!is_string($value) || $this->timestampSerializer->isValidString((string)$value)) {
      throw new RequestFieldTypeConversionException(
        RequestFieldType::TIMESTAMP,
        $key,
        $value
      );
    }

    // Convert to timestamp 
    return $this->timestampSerializer->deserialize((string)$value);
  }
}
