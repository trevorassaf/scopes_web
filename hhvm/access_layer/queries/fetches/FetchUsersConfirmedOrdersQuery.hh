<?hh // strict

class FetchUsersConfirmedOrdersQuery {

  public function __construct(
    private FetchQuery<ConfirmedOrder> $fetchQuery,
    private ConfirmedOrdersTable $confirmedOrdersTable 
  ) {}

  public async function fetch(
    UnsignedInt $user_id
  ): Awaitable<ImmVector<ConfirmedOrder>> {
    return await $this->fetchQuery->fetch(
      ImmMap{
        $this->confirmedOrdersTable->getUserIdKey() => $user_id->getNumber(),
      }
    ); 
  }
}
