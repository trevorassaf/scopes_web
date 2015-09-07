<?hh // strict

class IrregularTime implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $irregularDateId,
    private Time $startTime,
    private Time $endTime
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getIrregularDateid(): UnsignedInt {
    return $this->irregularDateId;
  }

  public function getStartTime(): Time {
    return $this->startTime;
  }

  public function getEndTime(): Time {
    return $this->endTime;
  }
}
