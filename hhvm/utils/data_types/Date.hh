<?hh // strict

class Date {

  const string DATE_FORMAT = "Y-m-d";

  public static function getFormat(): string {
    return self::DATE_FORMAT;
  }

  public static function isValid(string $date): bool {
    return DateTime::createFromFormat(self::getFormat(), $date) == false;  
  }

  public function __construct(
    private string $date    
  ) {}

  public function toString(): string {
    return $this->date;
  }

  public function isBefore(Date $date): bool {
    return $this->date < $date->toString();
  }
    
  public function isAfter(Date $date): bool {
    return $this->date > $date->toString();
  }
  
  public function equals(Date $date): bool {
    return $this->date == $date->toString();
  }

  public function toDayOfTheWeek(): DayOfTheWeekType {
    $date_index = (date("w", $this->toString()) + 6) % 7;
    return DayOfTheWeekType::assert($date_index);
  }
}
