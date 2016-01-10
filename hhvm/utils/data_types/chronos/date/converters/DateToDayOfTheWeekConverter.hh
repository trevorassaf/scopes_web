<?hh // strict

class DateToDayOfTheWeekConverter {

  const string PHP_DATE_TIME_FORMAT = "Y-m-d";

  public function __construct(
    private DateSerializer $dateSerializer
  ) {}

  public function convert(Date $date): DayOfTheWeekType {
    $date_str = $this->dateSerializer->serialize($date);
    $php_date_time_object = DateTime::createFromFormat(
      $this->dateSerializer->getFormat(),
      $date_str
    );
    $week_day_ordinal = $php_date_time_object->format("w");
    return DayOfTheWeekType::assert($week_day_ordinal);
  }
}
