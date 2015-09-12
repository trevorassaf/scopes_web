<?hh // strict

class TimeInterval {

  public function __construct(
    private Time $start,
    private Time $end
  ) {
    invariant($this->start->isBefore($this->end), "Start time must preceed end time!");
  }

  public function getStart(): Time {
    return $this->start;
  }

  public function getEnd(): Time {
    return $this->end;
  }

  public function toTimestampInterval(Date $date): TimestampInterval {
    return new TimestampInterval(
      new Timestamp(
        $date,
        $this->start
      ),
      new Timestamp(
        $date,
        $this->end
      )
    );
  }
}
