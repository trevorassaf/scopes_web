<?hh // strict

class IsValidReservedOrderMethod {

  public function __construct(
    private IsConflictingReservedOrderMethod $isConflictingReservedOrderMethod,
    private FetchRegularTimeQuery $fetchRegularTimeQuery,
    private FetchIrregularTimesQuery $fetchIrregularTimesQuery
  ) {}

  public function check(TimeInterval $interval): bool {
    try {
      // Initiate ir/regular time fetch queries
      $irregular_time_fetch_handle = $this->fetchIrregularTimeQuery->fetch(
        $interval->getDate()
      );
      
      $regular_time_fetch_handle = $this->fetchRegularTimeQuery->fetch(
        $interval->getDate()->toDayOfTheWeek()
      );  

      try {
        // Check to see if this violates the irregular time
        $irregular_times = $irregular_time_fetch_handle->getWaitHandle()->join();

        return $this->satisfiesIrregularTimes(
          $interval,
          $irregular_times
        );
      } catch (NonextantDateException $ex) {
        // Check to see if this violates the regular time
        $regular_time = $regular_time_fetch_handle->getWaitHandle()->join();

        return $this->satisfiesRegularTime(
          $interval,
          $regular_time
        );
      }
    } catch (QueryException $ex) {
      // TODO return specific exceptions for policy violations 
      throw new MethodException();
    } 
  }

  private function satisfiesIrregularTimes(
    TimeInterval $requested_interval,
    ImmVector<TimeInterval> $allowed_time_intervals
  ): bool {
    foreach ($allowed_time_intervals as $time_interval) {
      if (!$requested_interval->getStartTime()->isBefore($time_interval->getStartTime()) &&
          !$requested_interval->getEndTime()->isAfter($time_interval->getEndTime())) {
        return true; 
      }
    }
    return false; 
  }

  private function satisfiesRegularTimes(
    TimeInterval $requested_interval,
    TimeInterval $allowed_interval 
  ): bool {
    return !$requested_interval->getStartTime()->isBefore($allowed_interval->getStartTime()) &&
      !$requested_interval->getEndTime()->isAfter($allowed_interval->getEndTime());
  }
}
