<?hh // strict

class ApiTypeFieldConverter implements RequestFieldTypeConverter<ApiType> {

  public function convert(string $key, mixed $value): ApiType {
    error_log("ApiTypeFieldConverter::convert()");
    error_log(print_r($key, true));
    error_log(print_r($value, true));

    ob_start();
    var_dump($key);
    var_dump($value);
    $contents = ob_get_contents();
    ob_end_clean();
    error_log($contents);

    // Validate int type
    if (!is_numeric($value) || ApiType::isValid($value)) {
      throw new RequestFieldTypeConversionException(
        RequestFieldType::API_TYPE,
        $key,
        $value
      );
    }

    return ApiType::assert($value);
  }
}
