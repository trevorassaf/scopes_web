<?hh // strict

class DeleteByIdQuery<Tmodel> {

  public function __construct(
    private DeleteQuery<Tmodel> $deleteQuery,
    private Table<Tmodel> $table,
    private WhereClauseBuilder $whereClauseBuilder,
    private TermBuilder $termBuilder
  ) {}

  public async function delete(
    UnsignedInt $id
  ): Awaitable<void> {
    await $this->deleteQuery->delete(
      $this->whereClauseBuilder->setFirst(
        $this->termBuilder->equalTo(
          $this->table->getIdKey(),
          $id->getNumber()
        )
      )
      ->build()
    ); 
  }
}
