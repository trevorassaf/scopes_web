<?hh // strict

class ApiTypeFieldConverter implements RequestFieldTypeConverter<ApiType> {

  public function convert(string $key, mixed $value): ApiType {
    // Validate int type
    if (!is_int($value) || ApiType::isValid($value)) {
      throw new RequestFieldTypeConversionException(
        RequestFieldType::API_TYPE,
        $key,
        $value
      );
    }

    return ApiType::assert($value);
  }
}
