<?hh // strict

class FloatFieldConverter implements RequestFieldTypeConverter<float> {

  public function convert(string $key, mixed $value): float {
    // Validate float type
    if (!is_float($value)) {
      throw new RequestFieldTypeConversionException(
        RequestFieldType::FLOAT,
        $key,
        $value
      );
    }

    // Convert to float 
    return (float)$value;
  }
}
