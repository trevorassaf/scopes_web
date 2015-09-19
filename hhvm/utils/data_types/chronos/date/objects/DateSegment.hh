<?hh // strict

class DateSegment {

  public function __construct(
    private Date $start,
    private Date $end
  ) {}

  public function getStart(): Date {
    return $this->start;
  }

  public function getEnd(): Date {
    return $this->end;
  }
}
