<?hh // strict

class DeleteByIdQuery<Tmodel> {

  public function __construct(
    private DeleteQuery<Tmodel> $deleteQuery,
    private Table<Tmodel> $table,
    private WhereClauseVectorBuilder $whereClauseBuilder
  ) {}

  public async function delete(
    UnsignedInt $id
  ): Awaitable<void> {
    await $this->deleteQuery->delete(
      $this->whereClauseBuilder->setFirstClause(
        new EqualsWhereClause(
          $this->table->getIdKey(),
          (string)$id->getNumber()
        )
      )
      ->build()
    ); 
  }
}
