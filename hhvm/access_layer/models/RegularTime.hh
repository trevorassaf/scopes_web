<?hh // strict

class RegularTime implements Model {

  public function __construct(
    private UnsignedInt $id,
    private Time $startTime,
    private Time $endTime
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getStartTime(): Time {
    return $this->startTime;
  }

  public function getEndTime(): Time {
    return $this->endTime;
  }
}
