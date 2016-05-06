<?hh // strict

class GetDisallowedWeekDaysMethod {

  public function __construct(
    private FetchAllRegularWeekDaysQuery $fetchQuery
  ) {}

  public function get(): ImmVector<UnsignedInt> {
    // Fetch regular week days
    $fetch_handle = $this->fetchQuery->fetch();

    $regular_week_days = $fetch_handle
      ->getWaitHandle()
      ->join();

    // Determined disallowed days from allowed regular week days
    $week_days = Vector{
      true,
      true,
      true,
      true,
      true,
      true,
      true,
    };

    foreach ($regular_week_days as $day) {
      $day_idx = (int)$day->getType();
      $week_days[$day_idx] = false; // Mark day allowed
    }

    $disallowed_week_days = Vector{};

    for ($i = 0; $i < $week_days->count(); ++$i) {
      if ($week_days[$i]) {
        $disallowed_week_days[] = new UnsignedInt($i);
      }
    }

    return $disallowed_week_days->toImmVector();
  }
}
