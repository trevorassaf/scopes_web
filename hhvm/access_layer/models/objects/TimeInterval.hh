<?hh // strict

class TimeInterval {

  public function __construct(
    Time $start,
    Time $end
  ) {
    invariant($this->start->before($this->end), "Start time must preceed end time!");
  }

  public function getStart(): Time {
    return $this->start;
  }

  public function getEnd(): Time {
    return $this->end;
  }
}
