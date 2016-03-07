<?hh // strict

class UnsignedFloatFieldConverter implements RequestFieldTypeConverter<UnsignedFloat> {

  private FloatFieldConverter $floatFieldConverter;

  public function __construct() {
    $this->floatFieldConverter = new FloatFieldConverter();
  }

  public function convert(string $key, mixed $value): UnsignedFloat {
    
    // Convert the value to float type
    $float_value = $this->floatFieldConverter->convert($key, $value);

    // Validate unsigned float type
    if (!UnsignedFloat::isUnsigned($float_value)) {
      throw new RequestFieldTypeConversionException(
        RequestFieldType::UNSIGNED_FLOAT,
        $key,
        $value
      );
    }

    return new UnsignedFloat($float_value);
  }
}
