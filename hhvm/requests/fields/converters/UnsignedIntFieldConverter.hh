<?hh // strict

class UnsignedIntFieldConverter implements RequestFieldTypeConverter<UnsignedInt> {

  public function convert(string $key, mixed $value): UnsignedInt {
    // Validate unsigned int type 
    if (!is_int($value) || UnsignedInt::isUnsigned((int)$value)) {
      throw RequestFieldTypeConversionException(
        RequestFieldType::UNSIGNED_INT,
        $key,
        $value
      );
    }

    // Convert to unsigned int
    return new UnsignedInt((int)$value);
  }
}
