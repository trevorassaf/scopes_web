<?hh // strict

class IntFieldConverter implements RequestFieldTypeConverter<int> {

  public function convert(string $key, mixed $value): int {
    // Validate int type
    if (!is_int($value)) {
      throw RequestFieldTypeConversionException(
        RequestFieldType::INT,
        $key,
        $value
      );
    }

    // Convert to int 
    return (int)$value;
  }
}
