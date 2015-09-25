<?hh // strict

class UpdateByIdQuery {

  public function __construct(
    private UpdateByUniqueKeyQuery $updateByUniqueKeyQuery
  ) {}

  public async function update(
    Table $table,
    ImmMap<string, mixed> $update_params,
    UnsignedInt $id
  ): Awaitable<void> {
    await $this->updateByUniqueKeyQuery->update(
      $table,
      $update_params,
      ImmMap{
        $table->getIdKey() => $id->getNumber(),
      }
    );
  }
}
