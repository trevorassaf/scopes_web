<?hh // strict

class CreateRegularTimeMethod {

  public function __construct(
    private InsertRegularTimeQuery $regularTimeInsertQuery,
    private FetchByUniqueKeyQuery<RegularTime> $fetchRegularTimeByUniqueKeyQuery,
    private RegularTimesTable $regularTimesTable
  ) {}

  public function create(
    Time $start_time,
    Time $end_time
  ): RegularTime {
    
    /* TODO: write deez codez!
    // Condition: start_time must preceed end_time
    if (!$start_time->before($end_time)) {
      throw new InvalidTimeOrderingException();
    }
     */

    try {
      // Attempt insert    
      $insert_query_handle = $this->regularTimeInsertQuery->insert(
        $start_time,
        $end_time
      ); 
      return $insert_query_handle
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {
      // Check for duplication 
      if ($this->isDuplicateRegularTime($start_time, $end_time)) {
        //throw new DuplicateRegularTimeException($start_time, $end_time);
      } 
      throw new MethodException();
    }
  }

  private function isDuplicateRegularTime(Time $start_time, Time $end_time): bool {
    $fetch_query_handle = $this->fetchRegularTimeByUniqueKeyQuery->fetch(
      ImmMap{
        $this->regularTimesTable->getStartTimeKey() => $start_time->toString(),
        $this->regularTimesTable->getEndTimeKey() => $end_time->toString(),
      }  
    );
    $regular_time = $fetch_query_handle
      ->getWaitHandle()
      ->join();
    return $regular_time != null;
  }
}
