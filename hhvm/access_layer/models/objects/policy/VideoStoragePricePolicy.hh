<?hh // strict

class VideoStoragePricePolicy {

  public function __construct(
    private UnsignedFloat $price,
    private Timestamp $timeEnacted,
    private UnsignedInt $numberFreeDays
  ) {}

  public function getPrice(): UnsignedFloat {
    return $this->price;
  }

  public function getTimeEnacted(): Timestamp {
    return $this->timeEnacted;
  }

  public function getNumberFreeDays(): UnsignedInt {
    return $this->numberFreeDays;
  }
}
