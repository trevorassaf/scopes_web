<?hh // strict

class DeleteByIdQuery<Tmodel> {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private Table<Tmodel> $table
  ) {}

  public async function delete(
    UnsignedInt $id
  ): Awaitable<void> {
    await $this->asyncMysqlConnection->query(
      $this->createQuery($id)
    );
  }

  private function createQuery(
    UnsignedInt $id
  ): string {
    return
      "DELETE FROM " . $this->table->getTableName() . " WHERE "
      . $this->table->getIdKey() . "="
      . $id->getNumber();
  }
}
