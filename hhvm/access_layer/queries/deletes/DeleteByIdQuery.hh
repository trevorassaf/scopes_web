<?hh // strict

class DeleteByIdQuery<Tmodel> {

  public function __construct(
    private DeleteQuery<Tmodel> $deleteQuery,
    private Table $table
  ) {}

  public async function delete(
    UnsignedInt $id
  ): Awaitable<void> {
    $where_clause_builder = new WhereClauseVectorBuilder();
    await $this->deleteQuery->delete(
      $where_clause_builder->setFirstClause(
        new EqualsWhereClause(
          $this->table->getIdKey(),
          (string)$id->getNumber()
        )
      )
      ->build()
    ); 
  }
}
