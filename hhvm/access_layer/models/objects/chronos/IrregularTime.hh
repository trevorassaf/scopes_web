<?hh // strict

class IrregularTime implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $irregularDateId,
    private TimeSegment $timeSegment
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getIrregularDateId(): UnsignedInt {
    return $this->irregularDateId;
  }

  public function getTimeSegment(): TimeSegment {
    return $this->timeSegment;
  }
}
