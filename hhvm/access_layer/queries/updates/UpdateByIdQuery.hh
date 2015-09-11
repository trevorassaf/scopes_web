<?hh // strict

class UpdateByIdQuery<Tmodel> {

  public function __construct(
    private UpdateByUniqueKeyQuery<Tmodel> $updateByUniqueKeyQuery,
    private Table<Tmodel> $table

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
