<?hh // strict

class DateBuilder {

  const int DEFAULT_VALUE = 0;

  private Year $year;
  private Month $month;
  private Day $day;
  private HRDateSerializer $hrDateSerializer;

  public function __construct() {
    $this->year = Year::fromInt(self::DEFAULT_VALUE);
    $this->month = Month::fromInt(self::DEFAULT_VALUE);
    $this->day = Day::fromInt(self::DEFAULT_VALUE);
    $this->hrDateSerializer = new HRDateSerializer();
  }

  public function setYear(Year $year): this {
    $this->year = $year;
    return $this;
  }

  public function setMonth(Month $month): this {
    $this->month = $month;
    return $this;
  }

  public function setDay(Day $day): this {
    $this->day = $day;
    return $this;
  }

  public function build(): Date {
    return new Date(
      $this->year,
      $this->month,
      $this->day
    );
  }
}
