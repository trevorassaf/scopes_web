<?hh // strict

class ShortCode implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $userId,
    private string $code,
    private string $alias
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getUserId(): UnsignedInt {
    return $this->userId;
  }

  public function getCode(): string {
    return $this->code;
  }

  public function getAlias(): string {
    return $this->alias;
  }
}
