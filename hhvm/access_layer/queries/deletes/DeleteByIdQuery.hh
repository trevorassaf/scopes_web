<?hh // strict

class DeleteByIdQuery {

  public function __construct(
    private DeleteQuery $deleteQuery
  ) {}

  public async function delete(
    Table $table,
    UnsignedInt $id
  ): Awaitable<bool> {
    $where_clause_builder = new WhereClauseVectorBuilder();

    // Execute delete by id query 
    $num_rows_affected = await $this->deleteQuery->delete(
      $table,
      $where_clause_builder->setFirstClause(
        new EqualsWhereClause(
          $table->getIdKey(),
          (string)$id->getNumber()
        )
      )
      ->build()
    ); 

    // Hard fail if delete by id query affects more than 1 row
    invariant(
      $num_rows_affected->getNumber() <= 1,
      "Delete by id query must return either 1 or 0"
    );

    return $num_rows_affected === 1;
  }
}
