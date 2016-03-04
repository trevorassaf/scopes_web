<?hh // strict

class ShortCodeApiObject {

  const string ID_KEY = "id";
  const string CODE_KEY = "code";

  public function __construct(
    private int $id,
    private string $code
  ) {}

  public function getResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::ID_KEY => $this->id,
      self::CODE_KEY => $this->code,
    };
  }
}
