<?hh // strict

class FetchByIdQuery<Tmodel> {

  public function __construct(
    private FetchByUniqueKeyQuery<Tmodel> $fetchByUniqueKeyQuery
  ) {}

  public async function fetch(
    UnsignedInt $id
  ): Awaitable<?Tmodel> {
    return await $this->fetchByUniqueKeyQuery->fetch(
      ImmMap{
        $this->fetchByUniqueKeyQuery->getTable()->getIdKey() => $id->getNumber(),
      }
    );
  }
}
