<?hh // strict

class UpdateByIdQuery<Tmodel> {

  public function __construct(
    private UpdateByUniqueKeyQuery<Tmodel> $updateByUniqueKeyQuery
  ) {}

  public async function update(
    ImmMap<string, mixed> $update_params,
    UnsignedInt $id
  ): Awaitable<void> {
    return await $this->updateByUniqueKeyQuery->update(
      ImmMap{
        $this->updateByUniqueKeyQuery->getTable()->getIdKey() => $id->getNumber(),
      }
    );
  }
}
