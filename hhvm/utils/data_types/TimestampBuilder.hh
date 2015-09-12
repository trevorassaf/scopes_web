<?hh // strict

class TimestampBuilder {

  public function now(): Timestamp {
    $current_date_time = new DateTime();
    return Timestamp::fromString(
      $current_date_time->format(Timestamp::getFormat())
    );
  }
}
