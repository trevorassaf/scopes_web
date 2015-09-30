<?hh // strict

class IntFieldConverter implements RequestFieldTypeConverter<int> {

  public function convert(string $key, mixed $value): int {
    if (filter_var($value, FILTER_VALIDATE_INT) === false) {
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
