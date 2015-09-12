<?hh // strict

class UpdateByIdQuery {

  public function __construct(
    private UpdateByUniqueKeyQuery $updateByUniqueKeyQuery,
    private Table $table

  ) {}

  public async function update(
    ImmMap<string, mixed> $update_params,
    UnsignedInt $id
  ): Awaitable<void> {
    await $this->updateByUniqueKeyQuery->update(
      $update_params,
      ImmMap{
        $this->table->getIdKey() => $id->getNumber(),
      }
    );
  }
}
