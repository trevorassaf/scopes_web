<?hh // strict

class FetchByIdQuery<Tmodel> {

  public function __construct(
    private FetchByUniqueKeyQuery<Tmodel> $fetchByUniqueKeyQuery,
    private Table<Tmodel> $table
  ) {}

  public async function fetch(
    UnsignedInt $id
  ): Awaitable<?Tmodel> {
    return await $this->fetchByUniqueKeyQuery->fetch(
      ImmMap{
        $this->table->getIdKey() => $id->getNumber(),
      }
    );
  }
}
