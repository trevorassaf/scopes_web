<?hh // strict

class BoolFieldConverter implements RequestFieldTypeConverter<bool> {

  public function convert(string $key, mixed $value): bool {
    // Validate bool type
    if (!is_bool($value)) {
      throw RequestFieldTypeConversionException(
        RequestFieldType::BOOL,
        $key,
        $value
      );
    }

    // Convert to bool 
    return (bool)$value;
  }
}
