<?hh

class OrderConfiguration {

  public function __construct(
      private UnsignedInt $id,
      private UnsignedInt $minutesPerIntervalCount,
      private UnsignedInt $pricePerIntervalCount,
      private UnsignedInt $scopesCount
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

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
