<?hh // strict

class CreateIrregularTimeMethod {

  public function __construct(
    private IrregularTimeInsertQuery $irregularTimeInsertQuery,
    private IrregularTimesTable $irregularTimesTable
  ) {}

  public function create(
    UnsignedInt $irregular_date_id,
    Time $start_time,
    Time $end_time
  ): IrregularTime {
    try {
      // Attempt insert
      $insert_query_handle = $this->irregularTimeInsertQuery->insert(
        $irregular_date_id,
        $start_time,
        $end_time
      ); 

      return $insert_query_handle
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {
      throw new MethodException(); 
    }
  }
}
