<?hh // strict

class IsValidReservedOrderMethod {

  public function __construct(
    private IsConflictingReservedOrderMethod $isConflictingReservedOrderMethod,
    private FetchByIdQuery<RegularWeekDay> $fetchRegularWeekDayByIdQuery,
    private FetchRegularTimesQuery $fetchRegularTimesByRegularWeekDayQuery,
    private FetchIrregularTimesQuery $fetchIrregularTimesByIrregularDateQuery,
    private FetchIrregularDateByDateQuery $fetchIrregularDateByDateQuery
  ) {}

  public function check(TimeInterval $interval): bool {
    try {
      // TODO must first fetch DateId
      // Initiate ir/regular time fetch queries
      $irregular_time_fetch_handle = $this->fetchIrregularTimeQuery->fetch(
        $interval->getDate()
      );
      
      $regular_time_fetch_handle = $this->fetchRegularTimesQuery->fetch(
        $interval->getDate()->toDayOfTheWeek()
      );  

      try {
        // Check to see if this violates the irregular time
        $irregular_times = $irregular_time_fetch_handle->getWaitHandle()->join();

        return $this->satisfiesAllowedTimes(
          $interval,
          $irregular_times
        );
      } catch (NonextantDateException $ex) {
        // Check to see if this violates the regular time
        $regular_times = $regular_time_fetch_handle->getWaitHandle()->join();

        return $this->satisfiesAllowedTimes(
          $interval,
          $regular_times
        );
      }
    } catch (QueryException $ex) {
      // TODO return specific exceptions for policy violations 
      throw new MethodException();
    } 
  }

  private function satisfiesAllowedTimes(
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
}
