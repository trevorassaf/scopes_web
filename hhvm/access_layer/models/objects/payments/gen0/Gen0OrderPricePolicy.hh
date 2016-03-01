<?hh // strict

class Gen0OrderPricePolicy implements Model {

  public function __construct(
    private UnsignedInt $id,
    private Timestamp $timeEnacted,
    private UnsignedFloat $price
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getTimeEnacted(): Timestamp {
    return $this->timeEnacted;
  }

  public function getPrice(): UnsignedFloat {
    return $this->price;
  }
}
