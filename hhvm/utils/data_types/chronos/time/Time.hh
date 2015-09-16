<?hh // strict

class Time {

  public function __construct(
    private Hour $hour,
    private Minute $minute,
    private Second $second
  ) {}

  public function getHour(): Hour {
    return $this->hour;
  }

  public function getMinute(): Minute {
    return $this->minute;
  }

  public function getSecond(): Second {
    return $this->second;
  }

  public function equals(Time $time): bool {
    return $this->hour->equals($time->getHour()) &&
      $this->minute->equals($time->getMinute()) &&
      $this->second->equals($time->getSecond());
  }

  public function isBefore(Time $time): bool {
    // Compare hour first
    if ($this->hour->isBefore($time->getHour())) {
      return true;
    }

    if ($this->hour->isAfter($time->getHour())) {
      return false;
    }

    // Hours are equal, so compare minutes
    if ($this->minute->isBefore($time->getMinute())) {
      return true;
    }

    if ($this->minute->isAfter($time->getMinute())) {
      return false;
    }

    // Hours and minutes are equal, so compare seconds
    return $this->second->isBefore($time->getSecond());
  }

  public function isAfter(Time $time): bool {
    return $time->isBefore($this);
  }
}
