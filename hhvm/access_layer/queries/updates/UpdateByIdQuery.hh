<?hh // strict

class UpdateByIdQuery<Tmodel> {

  public function __construct(
    private UpdateQuery<Tmodel> $updateQuery,
    private WhereClauseBuilder $whereClauseBuilder,
    private TermBuilder $termBuilder,
    private Table<Tmodel> $table
  ) {}

  public async function update(
    ImmMap<string, mixed> $update_params,
    UnsignedInt $id
  ): Awaitable<void> {
    await $this->updateQuery->update(
      $update_params,
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
