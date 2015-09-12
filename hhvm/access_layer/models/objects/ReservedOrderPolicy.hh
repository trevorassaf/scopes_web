<?hh // strict

class ReservedOrderPolicy implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $scopesCount
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getScopesCount(): UnsignedInt {
    return $this->scopesCount;
  }
}
