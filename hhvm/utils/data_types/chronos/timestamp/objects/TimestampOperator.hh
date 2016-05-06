<?hh // strict

class TimestampOperator {

  const int SECONDS_IN_MINUTE = 60;
  const int SECONDS_IN_HOUR = 3600;
  const int SECONDS_IN_DAY = 86400;
  const int MAX_SECONDS_IN_MONTH = 2678400;

  public function __construct(
    private HRTimestampSerializer $timestampSerializer
  ) {}

  public function addMonths(
    Timestamp $timestamp,
    UnsignedInt $months
  ): Timestamp {
    $seconds = $months->getNumber() * self::MAX_SECONDS_IN_MONTH;
    return $this->addSeconds($timestamp, new UnsignedInt($seconds));
  }

  public function addDays(
    Timestamp $timestamp,
    UnsignedInt $days
  ): Timestamp {
    $seconds = $days->getNumber() * self::SECONDS_IN_DAY;
    return $this->addSeconds($timestamp, new UnsignedInt($seconds));
  }

  public function addHours(
    Timestamp $timestamp,
    UnsignedInt $hours
  ): Timestamp {
    $seconds = $hours->getNumber() * self::SECONDS_IN_HOUR;
    return $this->addSeconds($timestamp, new UnsignedInt($seconds)
    );
  }

  public function addMinutes(
    Timestamp $timestamp,
    UnsignedInt $minutes
  ): Timestamp {
    $seconds = $minutes->getNumber() * self::SECONDS_IN_MINUTE;
    return $this->addSeconds(
      $timestamp,
      new UnsignedInt($seconds)
    ); 
  }

  public function addSeconds(
    Timestamp $timestamp,
    UnsignedInt $seconds
  ): Timestamp {
    $serialized_starting_timestamp = $this->timestampSerializer->serialize($timestamp);
    $starting_php_timestamp = new DateTime($serialized_starting_timestamp);
    $time_interval = new DateInterval("PT".(string)$seconds->getNumber()."S");
    $new_php_timestamp = $starting_php_timestamp->add($time_interval);
    $new_timestamp_string = $new_php_timestamp->format($this->timestampSerializer->getFormat());
    return $this->timestampSerializer->deserialize($new_timestamp_string);
  }
}
