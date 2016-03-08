<?hh // strict

class ShortCodeApiObject {

  const string ID_KEY = "id";
  const string CODE_KEY = "code";
  const string ALIAS_KEY = "alias";

  public function __construct(
    private UnsignedInt $id,
    private string $code,
    private string $alias
  ) {}

  public function getResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::ID_KEY => $this->id->getNumber(),
      self::CODE_KEY => $this->code,
      self::ALIAS_KEY => $this->alias,
    };
  }
}
