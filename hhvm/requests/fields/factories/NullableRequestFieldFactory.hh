<?hh // strict

class NullableRequestFieldFactory<Ttype> {

  public function __construct(
    private RequestFieldValidator<Ttype> $requestFieldValidator
  ) {}

  public function make(string $key, mixed $value = null): NullableRequestField<Ttype> {
    return new NullableRequestField(
      $this->requestFieldValidator,
      $key,
      $value
    );
  }
}
