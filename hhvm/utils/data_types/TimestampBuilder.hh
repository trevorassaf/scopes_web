<?hh // strict

class TimestampBuilder {

  const string DATE_TIME_FORMAT = "Y-m-d H:i:s";

  public function now(): Timestamp {
    $current_date_time = new DateTime();
    return new Timestamp(
      $current_date_time->format(self::DATE_TIME_FORMAT)
    );
  }

}
