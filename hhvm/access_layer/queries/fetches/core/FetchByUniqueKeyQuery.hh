<?hh // strict

class FetchByUniqueKeyQuery<Tmodel> {

  public function __construct(
    private FetchQuery<Tmodel> $fetchQuery,
    private ConstraintMapToConjunctiveWhereClauseTranslator $constraintMapToConjunctiveWhereClauseTranslator
  ) {} 

  public async function fetch(
    ImmMap<string, mixed> $params
  ): Awaitable<?Tmodel> {
    // Perform fetch
    $where_clause = $this->constraintMapToConjunctiveWhereClauseTranslator->translate($params);
    $fetch_params_builder = new FetchParamsBuilder();
    $result_set = await $this->fetchQuery->fetch(
      $fetch_params_builder
        ->setTable($this->fetchQuery->getTable())
        ->setWhereClause($where_clause)
        ->build() 
    );

    // We expect to receive at most one record from
    // the db. Check for extraneous records...
    if ($result_set->count() > 1) {
      throw new Exception(
        "Received more than one record during unique key query from table"
      ); 
    }

    return $result_set->count() === 0 ? null : $result_set[0];
  }

  public function getTable(): Table<Tmodel> {
    return $this->fetchQuery->getTable();
  }
}
