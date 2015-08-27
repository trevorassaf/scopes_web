<?hh // strict

class ApiFieldTypeValidator<Ttype> {

  public function __construct(
    private ?RequestMapper<Ttype> $requestMapper
  ) {}

  public function validate(mixed $value): Ttype {}

  protected function unpack(): Ttype {}
}
