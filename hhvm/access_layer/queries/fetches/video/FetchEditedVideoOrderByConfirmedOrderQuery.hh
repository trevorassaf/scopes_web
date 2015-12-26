<?hh // strict

class FetchEditedVideoOrderByConfirmedOrderQuery {

  public function __construct(
    private FetchByUniqueKeyQuery<EditedVideoOrder> $fetchEditedVideoOrderByUniqueKeyQuery,
    private EditedVideoOrderTable $editedVideoOrdersTable
  ) {}

  public async function fetch(UnsignedInt $confirmed_order_id): Awaitable<?EditedVideoOrder> {
    return await $this->fetchEditedVideoOrderByUniqueKeyQuery->fetch(
      ImmMap{
        $this->editedVideoOrdersTable->getConfirmedOrderIdKey() => $confirmed_order_id->getNumber(),
      }
    ); 
  }
}
