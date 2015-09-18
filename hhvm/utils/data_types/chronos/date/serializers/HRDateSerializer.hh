<?hh // strict

class HRDateSerializer implements DateSerializer {

  const string DELIMITER = "-";
  const string FORMAT = "Y-m-d";

  public function getFormat(): string {
    return self::FORMAT;
  }

  public function serialize(Date $date): string {
    return $date->getYear()->toString() . self::DELIMITER
      . $date->getMonth()->toString() . self::DELIMITER
      . $date->getDay()->toString();
  }

  public function deserialize(string $date_str): Date {
    invariant($this->isValidString($date_str), "invalid HRDateSerializer!");
    $date_tokens = explode(self::DELIMITER, $date_str);
    return new Date(
      new Year(new UnsignedInt((int)$date_tokens[0])),
      new Month(new UnsignedInt((int)$date_tokens[1])),
      new Day(new UnsignedInt((int)$date_tokens[2]))
    );
  }

  public function isValidString(string $date_str): bool {
    $date_tokens = explode(self::DELIMITER, $date_str);
    if (count($date_tokens) != 3) {
      return false;
    }

    // Verify unsigned ints
    foreach ($date_tokens as $token) {
      if (!UnsignedInt::isValidString($token)) {
        return false;
      }
    }

    $year_number = UnsignedInt::fromString($date_tokens[0]);
    $month_number = UnsignedInt::fromString($date_tokens[1]);
    $day_number = UnsignedInt::fromString($date_tokens[2]);

    // Check date components
    if (!Month::isValid($month_number)
      && !Day::isValid($day_number)) 
    {
      return false; 
    }

    // Check integrity of date
    return checkdate(
      $month_number->getNumber(),
      $day_number->getNumber(),
      $year_number->getNumber()
    );
  }
}
