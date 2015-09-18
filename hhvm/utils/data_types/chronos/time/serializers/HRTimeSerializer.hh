<?hh // strict

class HRTimeSerializer implements TimeSerializer {

  const string DELIMITER = ":";
  const string FORMAT = "H:m:s";

  public function getFormat(): string {
    return self::FORMAT;
  }

  public function serialize(Time $time): string {
    return $time->getHour()->toString() . self::DELIMITER . 
      $time->getMinute()->toString() . self::DELIMITER .
      $time->getSecond()->toString();  
  }

  public function deserialize(string $time_str): Time {
    invariant($this->isValidString($time_str), "invalid HRTimeSerializer!");
    $time_tokens = explode(self::DELIMITER, $time_str);
    return new Time(
      new Hour(new UnsignedInt((int)$time_tokens[0])),
      new Minute(new UnsignedInt((int)$time_tokens[1])),
      new Second(new UnsignedInt((int)$time_tokens[2]))
    );
  }

  public function isValidString(string $time_str): bool {
    $time_tokens = explode(self::DELIMITER, $time_str);
    if (count($time_tokens) != 3) {
      return false;
    }

    // Verify unsigned ints
    foreach ($time_tokens as $token) {
      if (!UnsignedInt::isValidString($token)) {
        return false;
      }
    }

    $hour_number = UnsignedInt::fromString($time_tokens[0]);
    $minute_number = UnsignedInt::fromString($time_tokens[1]);
    $second_number = UnsignedInt::fromString($time_tokens[2]);

    // Check time components
    return Hour::isValid($hour_number) && Minute::isValid($minute_number);
  }
}
