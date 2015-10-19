<?hh // strict

class OrderTimestampSegment {

  public function __construct(
    private TimestampSegment $timestampSegment,
    private UnsignedInt $scopesCount
  ) {}

  public function getTimestampSegment(): TimestampSegment {
    return $this->timestampSegment;
  }

  public function getScopesCount(): UnsignedInt {
    return $this->scopesCount;
  }
}
