<?hh // strict

class TimestampFieldConverter implements RequestFieldTypeConverter<Timestamp> {

  public function convert(string $key, mixed $value): Timestamp {
    // Validate int type
    if (!is_string($value) || Timestamp::isValid((string)$value)) {
      throw new RequestFieldTypeConversionException(
        RequestFieldType::TIMESTAMP,
        $key,
        $value
      );
    }

    // Convert to timestamp 
    return new Timestamp((string)$value);
  }
}
