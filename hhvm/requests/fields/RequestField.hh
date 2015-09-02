<?hh // strict

class RequestField<Ttype> {

  private Ttype $value;

  public function __construct(
    private RequestFieldValidator<Ttype> $requestFieldValidator,
    private string $key,
    mixed $value
  ) {
    $this->value = $this->requestFieldValidator->validate($this->key, $value);
  }

  public function get(): Ttype {
    return $this->value;
  }
}
