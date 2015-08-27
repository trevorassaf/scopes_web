<?hh // strict

class RequestFieldFactory<Ttype> {

  public function __construct(
    private RequestFieldValidator<Ttype> $requestFieldValidator
  ) {}

  public function make(string $key, mixed $value): RequestField<Ttype> {
    return new RequestField<Ttype>(
      $this->requestFieldValidator,
      $key,
      $value
    );
  }
}
