<?hh

class Order {
  
  public function __construct(
      private UnsignedInt $id,
      private UnsignedInt $scopesCount,
      private Timestamp $startTime,
      private UnsignedInt $reservedMinutesCount 
  ) {}

  public function getScopesCount(): UnsignedInt {
    return $this->scopesCount;
  }

  public function getStartTime(): Timestamp {
    return $this->startTime;
  }
  
  public function getReservedMinutesCount(): UnsignedInt {
    return $this->reservedMinutesCount;
  }

}
