<?hh // strict

class IntFieldConverter implements RequestFieldTypeConverter<int> {

  public function convert(string $key, mixed $value): int {
    // Validate int type
    if (!ctype_digit(strval($value))) {
      throw new RequestFieldTypeConversionException(
        RequestFieldType::INT,
        $key,
        $value
      );
    }

    // Convert to int 
    return (int)$value;
  }
}
