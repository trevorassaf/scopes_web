<?hh // strict

class RegularTime implements Model {

  public function __construct(
    private UnsignedInt $id,
    private TimeSegment $timeSegment
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getTimeSegment(): TimeSegment {
    return $this->timeSegment;    
  }
}
