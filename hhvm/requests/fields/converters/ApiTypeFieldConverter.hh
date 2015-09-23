<?hh // strict

class ApiTypeFieldConverter implements RequestFieldTypeConverter<ApiType> {

  private UnsignedIntFieldConverter $uintFieldConverter;

  public function __construct() {
    $this->uintFieldConverter = new UnsignedIntFieldConverter(); 
  }

  public function convert(string $key, mixed $value): ApiType {

    // Convert to uint
    $uint_value = $this->uintFieldConverter->convert($key, $value);
    
    // Validate int type
    if (!ApiType::isValid($uint_value->getNumber())) {
      throw new RequestFieldTypeConversionException(
        RequestFieldType::API_TYPE,
        $key,
        $value
      );
    }
    return ApiType::assert($uint_value->getNumber());
  }
}
