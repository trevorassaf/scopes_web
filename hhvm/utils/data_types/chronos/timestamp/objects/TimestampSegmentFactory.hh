<?hh // strict

class TimestampSegmentFactory {

  public function __construct(
    private HRTimestampSerializer $timestampSerializer
  ) {}

  public function make(
    private Timestamp $start,
    private Timestamp $end
  ): TimestampSegment {
    return new TimestampSegment(
      $this->timestampSerializer,
      $start,
      $end
    ); 
  }
}
