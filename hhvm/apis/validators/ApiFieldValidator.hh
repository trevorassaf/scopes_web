<?hh // strict

class ApiFieldValidator<T> {

  public function __construct(
    private ApiFieldLengthValidator $lengthValidator,
    private ApiFieldTypeValidator<T> $typeValidator
  ) {}

  public function validate(mixed $value): T {
     
  }
}
