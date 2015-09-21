<?hh // strict

class InsertQuery<Tmodel> {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private Table $table,
    private ConcreteModelFactory<Tmodel> $concreteModelFactory,
    private InsertQueryCreater $insertQueryCreater
  ) {}

  public async function insert(
    ImmMap<string, mixed> $params
  ): Awaitable<Tmodel> {
    $query_str = $this->insertQueryCreater->createQuery(
      $this->table->getName(),
      $params
    );
    var_dump($query_str);
    $insert_result = await $this->asyncMysqlConnection->query($query_str); 

    return $this->concreteModelFactory->extrudeWithId(
      new UnsignedInt($insert_result->lastInsertId()),
      $params
    );
  }
}
