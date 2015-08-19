<?hh // strict

class RsvdOrderFetchQuery {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private RsvdOrdersTable $rsvdOrdersTable 
  ) {}

  public async function fetch(
    UnsignedInt $id 
  ): Awaitable<?RsvdOrder> {
    $result_set = await $this->asyncMysqlConnection->query(
      $this->createQuery($id)
    ); 
    return $this->rsvdOrdersTable->extrude(
      $result_set->mapRowsTyped()[0]->toImmMap()
    );
  }

  private function createQuery(
    UnsignedInt $id
  ): string {
    return 
      "SELECT * FROM " . $this->rsvdOrdersTable->getTableName()
      . " WHERE " . $this->rsvdOrdersTable->getIdKey()
      . " = " . $id->getNumber(); 
  }
}
