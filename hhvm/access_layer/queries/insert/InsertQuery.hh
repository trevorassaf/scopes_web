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
    $insert_result = await $this->asyncMysqlConnection->query(
      $this->insertQueryCreater->createQuery(
        $this->table->getName(),
        $params
      )
    ); 

    return $this->concreteModelFactory->extrudeWithId(
      new UnsignedInt($insert_result->lastInsertId()),
      $params
    );
  }
}
