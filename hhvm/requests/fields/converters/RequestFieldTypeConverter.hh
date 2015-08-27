<?hh // strict

interface RequestFieldTypeConverter<Ttype> {

  public function convert(string $key, mixed $value): Ttype;
}
