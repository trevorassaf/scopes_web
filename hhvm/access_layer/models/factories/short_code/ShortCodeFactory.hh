<?hh // strict

class ShortCodeFactory extends ConcreteModelFactory<ShortCode> {

  public function __construct(
    private ShortCodeTable $shortCodesTable
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): ShortCode {
    return new ShortCode(
      $id,
      new UnsignedInt((int)$params[$this->shortCodesTable->getUserIdKey()]),
      (string)$params[$this->shortCodesTable->getCodeKey()]
    );
  } 
}
