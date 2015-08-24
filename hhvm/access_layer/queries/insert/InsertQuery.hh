<?hh // strict

class InsertQuery<Tmodel> {

  public function __construct(
      private AsyncMysqlConnection $asyncMysqlConnection,
      private Table<Tmodel> $table,
      private InsertQueryCreater $insertQueryCreater
  ) {}

  public async function insert(
    ImmMap<string, mixed> $params
  ): Awaitable<Tmodel> {
    $insert_result = await $this->asyncMysqlConnection->query(
      $this->insertQueryCreater->createQuery(
        $this->table->getTableName(),
        $params
      )
    ); 

    return $this->table->extrudeWithId(
      new UnsignedInt($insert_result->lastInsertId()),
      $params
    );
  }
}
