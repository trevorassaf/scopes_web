<?hh // strict

class SameDayTimeInterval {

  public function __construct(
    private Date $date,
    private TimeInterval $timeInterval
  ) {}

  public function getDate(): Date {
    return $this->date;
  }

  public function getTimeInterval(): TimeInterval {
    return $this->timeInterval;
  }
}
