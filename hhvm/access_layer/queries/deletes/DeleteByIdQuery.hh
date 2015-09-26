<?hh // strict

class DeleteByIdQuery {

  public function __construct(
    private DeleteQuery $deleteQuery
  ) {}

  public async function delete(
    Table $table,
    UnsignedInt $id
  ): Awaitable<void> {
    $where_clause_builder = new WhereClauseVectorBuilder();
    await $this->deleteQuery->delete(
      $table,
      $where_clause_builder->setFirstClause(
        new EqualsWhereClause(
          $table->getIdKey(),
          (string)$id->getNumber()
        )
      )
      ->build()
    ); 
  }
}
