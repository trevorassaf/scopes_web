<?hh // strict

class StringFieldConverter implements RequestFieldTypeConverter<string> {

  public function convert(string $key, mixed $value): string {
    // Validate string type
    if (!is_string($value)) {
      throw RequestFieldTypeConversionException(
        RequestFieldType::STRING,
        $key,
        $value
      );
    }

    // Convert to string
    return (string)$value;
  }
}
