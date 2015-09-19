<?hh // strict

class TimestampSegmentExpander {

  const string NEXT_DAY_FORMAT = "P1D";

  public function __construct(
    private HRDateSerializer $hrDateSerializer
  ) {}

  public function expand(TimestampSegment $timestamp_segment): ImmVector<SingleDayTimeSegment> {
    $time_segment_sequence = Vector{};
    $curr_date = $timestamp_segment->getStart()->getDate();
    $end_date = $timestamp_segment->getEnd()->getDate();

    // Check to see if timestamp segment begins/ends on the same day
    if ($curr_date->equals($end_date)) {
      $time_segment_sequence[] = new SingleDayTimeSegment(
        $curr_date,
        new TimeSegment(
          $timestamp_segment->getStart()->getTime(),
          $timestamp_segment->getEnd()->getTime(),
        )
      );
      return $time_segment_sequence->toImmVector();
    }

    // Push subsequent dates
    $php_date_interval = new DateInterval(self::NEXT_DAY_FORMAT);

    while ($curr_date->isBefore($end_date)) {
      // Push date
      $time_segment_sequence[] = new SingleDayTimeSegment(
        $curr_date,
        TimeSegment::fullDay()
      ); 

      // Advance to next date   
      $php_date_time = DateTime::createFromFormat(
        $this->hrDateSerializer->getFormat(),
        $this->hrDateSerializer->serialize($curr_date)
      );
      $php_next_date_time = $php_date_time->add($php_date_interval);
      $curr_date = $php_next_date_time->format($this->hrDateSerializer->getFormat());
    }

    // Add final date
    $time_segment_sequence[] = new SingleDayTimeSegment(
      $curr_date,
      TimeSegment::end($timestamp_segment->getEnd()->getTime())
    );

    return $time_segment_sequence->toImmVector();
  }
}
