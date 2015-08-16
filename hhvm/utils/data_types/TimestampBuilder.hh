<?hh // strict

class TimestampBuilder {

  public function now(): Timestamp {
    $current_date_time = new DateTime();
    return new Timestamp(
      $current_date_time->format(Timestamp::DATE_TIME_FORMAT)
    );
  }
}
