<?hh // strict

class TimestampSegment {

  public function __construct(
    private HRTimestampSerializer $timestampSerializer,
    private Timestamp $start,
    private Timestamp $end
  ) {
    invariant($this->start->isBefore($this->end), "Start time must preceed end time");
  }

  public function toTimeSegment(): TimeSegment {
    return new TimeSegment(
      $this->start->getTime(),
      $this->end->getTime()
    );
  }
  
  public function getStart(): Timestamp {
    return $this->start;
  }

  public function getEnd(): Timestamp {
    return $this->end;
  }

  public function getNumberOfHours(): UnsignedInt {
    $time_difference = $this->getTimeDifference();
    return $time_difference->getHour()->getNumber();
  }

  public function getTimeDifference(): Time {
    // Serialize timestamps
    $start_time_str = $this->timestampSerializer->serialize($this->start); 
    $end_time_str = $this->timestampSerializer->serialize($this->end); 

    // Convert to POPO
    $start_time_date_time = new DateTime($start_time_str);
    $end_time_date_time = new DateTime($end_time_str);

    // Calculate difference
    $time_difference = $end_time_date_time->diff($start_time_date_time);
    $hours = $time_difference->h + $time_difference->days * 24;
    $minutes = $time_difference->m;
    $seconds = $time_difference->s;

    return new Time(
      new Hour($hours),
      new Minute($minutes),
      new Second($seconds)
    );
  }
}
