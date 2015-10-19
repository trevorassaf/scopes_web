<?hh // strict

class FetchSingletonQuery<Tmodel> {

  const int ID = 1;

  public function __construct(
    private FetchByIdQuery<Tmodel> $fetchByIdQuery
  ) {}

  public async function fetch(): Awaitable<Tmodel> {
    $result = await $this->fetchByIdQuery->fetch(
      new UnsignedInt(self::ID)
    ); 

    invariant($result != null, "Singleton record should not be null!");

    return $result;
  }
}
