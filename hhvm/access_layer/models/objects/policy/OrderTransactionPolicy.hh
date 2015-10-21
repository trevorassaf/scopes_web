<?hh // strict

class OrderTransactionPolicy {

  public function __construct(
    private UnsignedInt $daysBeforeCharge,
    private Timestamp $timeEnacted 
  ) {}

  public function getDaysBeforeCharge(): UnsignedInt {
    return $this->daysBeforeCharge;
  }

  public function getTimeEnacted(): Timestamp {
    return $this->timeEnacted;
  }
}
