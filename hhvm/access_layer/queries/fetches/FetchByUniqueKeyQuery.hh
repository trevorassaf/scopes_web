<?hh // strict

class FetchByUniqueKeyQuery<Tmodel> {

  public function __construct(
    private FetchQuery<Tmodel> $fetchQuery,
    private Table<Tmodel> $table
  ) {} 

  public async function fetch(
    ImmMap<string, mixed> $params
  ): Awaitable<?Tmodel> {
    $result_set = await $this->fetchQuery->fetch($params);

    // We expect to receive at most one record from
    // the db. Check for extraneous records...
    if ($result_set->count() > 1) {
      throw new Exception(
        "Received more than one record during unique key query from table"
      ); 
    }

    return $result_set->count() === 0 ? null : $result_set[0];
  }

  private function translateConstraintMapToConjunctiveWhereClause(
    ImmMap<string, mixed> $params
  ): WhereClause {
    
  }

  public function getTable(): Table<Tmodel> {
    return $this->fetchQuery->getTable();
  }
}
