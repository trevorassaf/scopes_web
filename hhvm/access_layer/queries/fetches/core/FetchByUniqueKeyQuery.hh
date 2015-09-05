<?hh // strict

class FetchByUniqueKeyQuery<Tmodel> {

  public function __construct(
    private FetchQuery<Tmodel> $fetchQuery,
    private Table<Tmodel> $table,
    private ConstraintMapToConjunctiveWhereClauseTranslator $constraintMapToConjunctiveWhereClauseTranslator
  ) {} 

  public async function fetch(
    ImmMap<string, mixed> $params
  ): Awaitable<?Tmodel> {
    // Perform fetch
    $result_set = await $this->fetchQuery->fetch(
      $this->constraintMapToConjunctiveWhereClauseTranslator->translate($params)
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