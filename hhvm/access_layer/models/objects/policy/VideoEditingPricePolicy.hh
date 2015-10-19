<?hh // strict

class VideoEditingPricePolicy {

  public function __construct(
    private UnsignedFloat $price,
    private Timestamp $timeEnacted
  ) {}

  public function getPrice(): UnsignedFloat {
    return $this->price;
  }

  public function getTimeEnacted(): Timestamp {
    return $this->timeEnacted;
  }
}
