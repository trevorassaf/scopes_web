<?hh // strict

class TimeInterval {

  public function __construct(
    private Time $start,
    private Time $end
  ) {}

  public function getStart(): Time {
    return $this->start;
  }

  public function getEnd(): Time {
    return $this->end;
  }
}
