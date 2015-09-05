<?hh // strict

class UpdateByUniqueKeyQuery<Tmodel> {

  public function __construct(
    private UpdateQuery<Tmodel> $updateQuery,
    private Table<Tmodel> $table,
    private ConstraintMapToConjunctiveWhereClauseTranslator $constraintMapToConjunctiveWhereClauseTranslator
  ) {}

  public async function update(): Awaitable<?Tmodel> {
    ImmMap<string, mixed> $params
  ): Awaitable<?Tmodel> {
    // Perform fetch
    $result_set = await $this->updateQuery->update(
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
    return $this->updateQuery->getTable();
  }
}
