<?hh // strict

class DateSegmentExpander {

  const string NEXT_DAY_FORMAT = "P1D";

  public function __construct(
    private HRDateSerializer $hrDateSerializer
  ) {}

  public function expand(DateSegment $interval): ImmVector<Date> {
    $date_vector = Vector{};
    $curr_date = $interval->getStart();
    $php_date_interval = new DateInterval(self::NEXT_DAY_FORMAT);

    while (!$curr_date->isAfter($interval->getEnd())) {
      // Push date
      $date_vector[] = $curr_date;

      // Advance to next date
      $php_date_time = DateTime::createFromFormat(
        $this->hrDateSerializer->getFormat(),
        $this->hrDateSerializer->serialize($curr_date)
      );
      $php_next_date_time = $php_date_time->add($php_date_interval);
      $curr_date = $php_next_date_time->format($this->hrDateSerializer->getFormat());
    }

    return $date_vector->toImmVector();
  }
}
