<?hh // strict

class CreateRegularWeekDayMethod {

  public function __construct(
    private InsertRegularWeekDayQuery $regularWeekDayInsertQuery,
    private FetchByIdQuery<RegularWeekDay> $fetchRegularWeekDayByIdQuery,
    private RegularWeekDaysTable $regularWeekDaysQuery
  ) {}

  public function create(
    DayOfTheWeekType $day 
  ): RegularWeekDay {
    try {
      // Attempt insert 
      $insert_query_handle = $this->regularWeekDayInsertQuery->insert(
        new UnsignedInt((int)$day)
      );
      return $insert_query_handle
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {
      // Check for duplicate day of the week 
      if ($this->isDuplicateDay($day)) {
        //throw new DuplicateRegularWeekDayException($day);
      } 
      throw new MethodException();
    }
  }

  private function isDuplicateDay(DayOfTheWeekType $day): bool {
    $fetch_query_handle = $this->fetchRegularWeekDayByIdQuery->fetch(
      new UnsignedInt((int)$day)
    );
    $regular_week_day = $fetch_query_handle
      ->getWaitHandle()
      ->join();
    return $regular_week_day != null;
  }
}
