<?hh // strict

class RequestFieldValidator<Ttype> {

  public function __construct(
    private RequestFieldTypeConverter<Ttype> $requestFieldTypeConverter,
    private ImmVector<RequestFieldConstraint<Ttype>> $requestFieldConstraints
  ) {}

  public function validate(string $key, mixed $value): Ttype {
    $converted_value = $this->requestFieldTypeConverter->convert($key, $value);
    foreach ($this->requestFieldConstraints as $field_constraint) {
      $field_constraint->apply($key, $converted_value);
    }
    return $converted_value;
  }
}
