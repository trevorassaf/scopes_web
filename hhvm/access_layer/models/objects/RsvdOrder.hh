<?hh // strict

class RsvdOrder implements Model {
  
  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $userId, 
    private UnsignedInt $scopesCount,
    private TimestampSegment $timestampSegment
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getUserId(): UnsignedInt {
    return $this->userId;
  }

  public function getScopesCount(): UnsignedInt {
    return $this->scopesCount;
  }

  public function getTimestampSegment(): TimestampSegment {
    return $this->timestampSegment;
  }
}
