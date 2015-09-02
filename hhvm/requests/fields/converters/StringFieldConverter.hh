<?hh // strict

class StringFieldConverter implements RequestFieldTypeConverter<string> {

  public function convert(string $key, mixed $value): string {
    // Validate string type
    if (!is_string($value)) {
      throw new RequestFieldTypeConversionException(
        RequestFieldType::STRING,
        $key,
        $value
      );
    }

    // Convert to string
    return (string)$value;
  }
}
