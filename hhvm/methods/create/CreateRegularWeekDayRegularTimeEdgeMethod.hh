<?hh // strict

class CreateRegularWeekDayRegularTimeEdgeMethod {

  public function __construct(
    private RegularWeekDayRegularTimeEdgeInsertQuery $edgeInsertQuery,
    private FetchByUniqueKeyQuery<RegularWeekDayRegularTimeEdge> $fetchEdgeByUniqueKeyQuery,
    private RegularWeekDayRegularTimeEdgesTable $edgesTable
  ) {}

  public function create(
    UnsignedInt $day_id,
    UnsignedInt $time_id
  ): RegularWeekDayRegularTimeEdge {
    try {
      // Attempt query 
      $insert_query_handle = $this->edgeInsertQuery->insert(
        $day_id,
        $time_id
      );
      return $insert_query_handle
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {
      if ($this->isDuplicateEdge($day_id, $time_id)) {
        //throw new DuplicateRegularWeekDayTimeEdgeException($day_id, $time_id);
      } 
      throw new MethodException();
    }
  }

  private function isDuplicateEdge(
    UnsignedInt $day_id,
    UnsignedInt $time_id
  ): bool {
    $fetch_query_handle = $this->fetchEdgeByUniqueKeyQuery->fetch(
      ImmMap{
        $this->edgesTable->getRegularWeekDayIdKey() => $day_id,
        $this->edgesTable->getRegularTimeIdKey() => $time_id,
      }
    );
    $edge = $fetch_query_handle
      ->getWaitHandle()
      ->join();
    return $edge != null;
  }
}
