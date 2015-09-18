<?hh // strict

class Timestamp {
  
  public function __construct(
    private Date $date,
    private Time $time 
  ) {}

  public function getDate(): Date {
    return $this->date;
  }

  public function getTime(): Time {
    return $this->time;
  }

  public function isBefore(Timestamp $timestamp): bool {
    return $this->date->isBefore($timestamp->getDate()) ||
      $this->date->equals($timestamp->getDate()) &&
      $this->time->isBefore($timestamp->getTime());
  }
    
  public function isAfter(Timestamp $timestamp): bool {
    return $this->date->isAfter($timestamp->getDate()) ||
      $this->date->equals($timestamp->getDate()) &&
      $this->time->isBefore($timestamp->getTime());
  }
  
  public function equals(Timestamp $timestamp): bool {
    return $this->date->equals($timestamp->getDate()) &&
      $this->time->equals($timestamp->getTime());
  }
}
