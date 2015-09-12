<?hh // strict

class Timestamp {
  
  public static function getFormat(): string {
    return Date::getFormat() . " " . Time::getFormat(); 
  }

  public static function isValid(string $timestamp): bool {
    return DateTime::createFromFormat(self::getFormat(), $timestamp) == false; 
  }

  public static function fromString(string $timestamp): Timestamp {
    invariant(self::isValid($timestamp), "Invalid timestamp string format!");
    $date_time = DateTime::createFromFormat(self::getFormat(), $timestamp);
    return new Timestamp(
      new Date($date_time->format(Date::getFormat())),
      new Time($date_time->format(Time::getFormat()))
    );
  }

  public function __construct(
    private Date $date,
    private Time $time 
  ) {}

  public function toString(): string {
    return $this->date->toString() . " " . $this->time->toString();
  }

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
