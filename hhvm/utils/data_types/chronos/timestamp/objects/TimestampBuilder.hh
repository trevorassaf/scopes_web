<?hh // strict

class TimestampBuilder {

  public function __construct(
    private TimestampSerializer $timestampSerializer
  ) {}

  public function now(): Timestamp {
    $php_current_date_time = new DateTime();
    return $this->timestampSerializer->deserialize(
      $php_current_date_time->format($this->timestampSerializer->getFormat())
    );
  }

  public function fromUnserializedApiTimestamp(UnserializedTimestampApiRequest $api_timestamp): Timestamp {
    $api_date = $api_timestamp->getDate(); 
    $api_time = $api_timestamp->getTime();

    // Assemble Date object
    $year = new Year($api_date->getYear()->get());
    $month = new Month($api_date->getMonth()->get());
    $day = new Day($api_date->getDate()->get());

    $date = new Date(
      $year,
      $month,
      $day
    );

    // Assemble Time object
    $hours = new Hour($api_time->getHours()->get());
    $minutes = new Minute($api_time->getMinutes()->get());
    $seconds = new Second($api_time->getSeconds()->get());

    $time = new Time(
      $hours,
      $minutes,
      $seconds
    );

    return new Timestamp($date, $time);
  }
}
