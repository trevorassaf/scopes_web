<?hh // strict

class RsvdOrderDeleteQuery {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private RsvdOrdersTable $rsvdOrdersTable 
  ) {}

  public async function delete(
  ): Awaitable<void> {}
}
