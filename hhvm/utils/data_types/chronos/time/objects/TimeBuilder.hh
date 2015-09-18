<?hh // strict

class TimeBuilder {

  const int DEFAULT_VALUE = 0;

  private Hour $hour;
  private Minute $minute;
  private Second $second;

  public function __construct() {
    $this->hour = new Hour(new UnsignedInt(self::DEFAULT_VALUE));
    $this->minute = new Minute(new UnsignedInt(self::DEFAULT_VALUE));
    $this->second = new Second(new UnsignedInt(self::DEFAULT_VALUE));
  }

  public function setHour(Hour $hour): this {
    $this->hour = $hour;
    return $this; 
  }

  public function setMinute(Minute $minute): this {
    $this->minute = $minute;
    return $this;
  }

  public function setSecond(Second $second): this {
    $this->second = $second;
    return $this;
  }

  public function build(): Time {
    return new Time(
      $this->hour,
      $this->minute,
      $this->second
    );
  }
}
