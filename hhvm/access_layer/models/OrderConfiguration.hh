<?hh

class OrderConfiguration {

  public function __construct(
      private UnsignedInt $minutesPerIntervalCount,
      private UnsignedInt $pricePerIntervalCount,
      private UnsignedInt $scopesCount
  ) {}

  public function getMinutesPerIntervalCount(): UnsignedInt {
    return $this->minutesPerIntervalCount; 
  }

  public function getPricePerIntervalCount(): UnsignedInt {
    return $this->pricePerIntervalCount;
  }

  public function getScopesCount(): UnsignedInt {
    return $this->scopesCount;
  }
}
