<?hh // strict

class MultiDayTimeInterval {

  public function __construct(
    private Timestamp $start,
    private Timestamp $end
  ) {}

  public function getStart(): Timestamp {
    return $this->start;
  }

  public function getEnd(): Timestamp {
    return $this->end;
  }
}
