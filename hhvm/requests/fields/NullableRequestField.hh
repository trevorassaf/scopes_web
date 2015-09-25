<?hh // strict

class NullableRequestField<Ttype> {

  private ?Ttype $value;

  public function __construct(
    private RequestFieldValidator<Ttype> $requestFieldValidator,
    private string $key,
    mixed $value
  ) {
    $this->value = ($value === null)
      ? null
      : $this->requestFieldValidator->validate($this->key, $value);
  }

  public function get(): ?Ttype {
    return $this->value;
  }
}
