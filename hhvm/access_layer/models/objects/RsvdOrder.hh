<?hh // strict

class RsvdOrder implements Model {
  
  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $userId, 
    private UnsignedInt $scopesCount,
    private Timestamp $startTime,
    private Timestamp $endTime
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

  public function getStartTime(): Timestamp {
    return $this->startTime;
  }
  
  public function getEndTime(): Timestamp {
    return $this->endTime;
  }

}
