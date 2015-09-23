<?hh // strict

class StringFieldConverter implements RequestFieldTypeConverter<string> {

  public function convert(string $key, mixed $value): string {
ob_start();
var_dump($key);
var_dump($value);
$contents = ob_get_contents();
ob_end_clean();
error_log($contents);

    // Validate string type
    if (!is_string($value)) {

      throw new RequestFieldTypeConversionException(
        RequestFieldType::STRING,
        $key,
        $value
      );
    }

    // Convert to string
    return (string)$value;
  }
}
