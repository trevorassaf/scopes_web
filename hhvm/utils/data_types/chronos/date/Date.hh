<?hh // strict

class Date {

  public function __construct(
    private Year $year,
    private Month $month,
    private Day $day
  ) {}

  public function getYear(): Year {
    return $this->year;
  }

  public function getMonth(): Month {
    return $this->month;
  }

  public function getDay(): Day {
    return $this->day;
  }

  public function isBefore(Date $date): bool {
    // Compare years
    if ($this->year->isBefore($date->getYear())) {
      return true;
    }

    if ($this->year->isAfter($date->getYear())) {
      return false;
    }

    // Years are equal, compare months
    if ($this->month->isBefore($date->getMonth())) {
      return true;
    }

    if ($this->month->isAfter($date->getMonth())) {
      return false;
    }

    // Years and months are equal, compare days
    return $this->day->isBefore($date->getDay());
  }
    
  public function isAfter(Date $date): bool {
    return $date->isBefore($this);
  }
  
  public function equals(Date $date): bool {
    return $this->year->equals($date->getYear()) &&
      $this->month->equals($date->getMonth()) &&
      $this->day->equals($date->getDay());
  }
}
