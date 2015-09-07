<?hh // strict

class Date {

  const string DATE_FORMAT = "Y-m-d";

  public static function isValid(string $date): bool {
    return new DateTime::fromFormat(self::DATE_FORMAT, $date) == false;  
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
}
