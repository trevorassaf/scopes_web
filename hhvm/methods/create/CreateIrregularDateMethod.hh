<?hh // strict

class CreateIrregularDateMethod {

  public function __construct(
    private InsertIrregularDateQuery $irregularTimeInsertQuery,
    private FetchByUniqueKeyQuery<IrregularDate> $fetchIrregularDateByUniqueQuery,
    private IrregularDatesTable $irregularDatesTable
  ) {}

  public function create(
    Date $date
  ): IrregularDate {
    try {
      // Attempt insert
      $insert_query_handle = $this->irregularTimeInsertQuery->insert($date);
      return $insert_query_handle
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {
      // Check for duplication
      if ($this->isDuplicateIrregularDate($date)) {
        //throw new DuplicateIrregularDateException($date);  
      } 
      throw new MethodException(); 
    }
  }

  private function isDuplicateIrregularDate(Date $date): bool {
    $fetch_query_handle = $this->fetchIrregularDateByUniqueQuery->fetch(
      ImmMap{
        $this->irregularDatesTable->getDateKey() => $date->toString(), 
      }
    );   
    $irregular_date = $fetch_query_handle
      ->getWaitHandle()
      ->join();
    return $irregular_date != null;
  }
}
