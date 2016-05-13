<?hh // strict

class MixedFieldConverter implements RequestFieldTypeConverter<mixed> {

  public function convert(string $key, mixed $value): mixed {
    return $value;
  }
}
