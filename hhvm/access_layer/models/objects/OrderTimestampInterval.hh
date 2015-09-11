<?hh // strict

class OrderTimestampInterval {

  public function __construct(
    private TimestampInterval $timestampInterval,
    private UnsignedInt $scopesCount
  ) {}

  public function getTimestampInterval(): TimestampInterval {
    return $this->timestampInterval;
  }

  public function getScopesCount(): UnsignedInt {
    return $this->scopesCount;
  }
}
