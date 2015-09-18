<?hh // strict

class TimestampBuilder {

  public function __construct(
    private TimestampSerializer $timestampSerializer
  ) {}

  public function now(): Timestamp {
    $current_date_time = new DateTime();
    return $this->timestampSerializer->deserialize(
      $current_date_time->format($this->timestampSerializer->getFormat())
    );
  }
}
