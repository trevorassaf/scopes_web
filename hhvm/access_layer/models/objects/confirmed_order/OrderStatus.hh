<?hh // strict

class OrderStatus implements Model {

  public function __construct(
    private UnsignedInt $id,
    private string $name
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getName(): string {
    return $this->name;
  }
}
