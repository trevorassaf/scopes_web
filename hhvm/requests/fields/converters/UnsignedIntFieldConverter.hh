<?hh // strict

class UnsignedIntFieldConverter implements RequestFieldTypeConverter<UnsignedInt> {

  private IntFieldConverter $intFieldConverter;

  public function __construct() {
    $this->intFieldConverter = new IntFieldConverter(); 
  }

  public function convert(string $key, mixed $value): UnsignedInt {

    // Convert the value to int type
    $int_value = $this->intFieldConverter->convert($key, $value);
    
    // Validate unsigned int type 
    if (!UnsignedInt::isUnsigned($int_value)) {
      throw new RequestFieldTypeConversionException(
        RequestFieldType::UNSIGNED_INT,
        $key,
        $value
      );
    }

    // Convert to unsigned int
    return new UnsignedInt($int_value);
  }
}
