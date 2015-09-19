<?hh // strict

class TimeSegment {

  const int FULL_DAY_START_HOUR = 0;
  const int FULL_DAY_END_HOUR = 24;

  public static function end(Time $end_time): TimeSegment {
    $time_builder = new TimeBuilder();
    return new TimeSegment(
      $time_builder->build(),
      $end_time
    );
  }

  public static function fullDay(): TimeSegment {
    $time_builder = new TimeBuilder();

    $start_hour = new Hour(
      new UnsignedInt(self::FULL_DAY_START_HOUR)
    );
    $end_hour = new Hour(
      new UnsignedInt(self::FULL_DAY_END_HOUR)
    );

    return new TimeSegment(
      $time_builder
        ->setHour($start_hour)
        ->build(),
      $time_builder
        ->setHour($end_hour)
        ->build()
    );
  }

  public function __construct(
    private Time $start,
    private Time $end
  ) {
    invariant($this->start->isBefore($this->end), "Start time must preceed end time!");
  }

  public function getStart(): Time {
    return $this->start;
  }

  public function getEnd(): Time {
    return $this->end;
  }

  public function toTimestampSegment(Date $date): TimestampSegment {
    return new TimestampSegment(
      new Timestamp(
        $date,
        $this->start
      ),
      new Timestamp(
        $date,
        $this->end
      )
    );
  }
}
