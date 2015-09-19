<?hh // strict

class SingleDayTimeSegment {

  public function __construct(
    private Date $date,
    private TimeSegment $timeSegment
  ) {}

  public function getDate(): Date {
    return $this->date;
  }

  public function getTimeSegment(): TimeSegment {
    return $this->timeSegment;
  }
}
