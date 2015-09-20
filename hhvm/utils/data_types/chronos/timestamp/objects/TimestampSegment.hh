<?hh // strict

class TimestampSegment {

  public function __construct(
    private Timestamp $start,
    private Timestamp $end
  ) {
    invariant($this->start->isBefore($this->end), "Start time must preceed end time");
  }

  public function toTimeSegment(): TimeSegment {
    return new TimeSegment(
      $this->start->getTime(),
      $this->end->getTime()
    );
  }
  
  public function getStart(): Timestamp {
    return $this->start;
  }

  public function getEnd(): Timestamp {
    return $this->end;
  }
}
