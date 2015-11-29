<?hh // strict

class TimestampSegmentFactory {

  public function __construct(
    private HRTimestampSerializer $timestampSerializer
  ) {}

  public function make(
    Timestamp $start,
    Timestamp $end
  ): TimestampSegment {
    return new TimestampSegment(
      $this->timestampSerializer,
      $start,
      $end
    ); 
  }
}
