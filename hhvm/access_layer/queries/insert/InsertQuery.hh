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
    // Serialize insert query
    $query_str = $this->insertQueryCreater->createQuery(
      $this->table->getName(),
      $params
    );

var_dump($query_str);

    // Execute insert query
    $insert_result = await $this->asyncMysqlConnection->query($query_str); 

    // Check if insert query failed
    if ($insert_result instanceof AsyncMysqlQueryErrorResult) {
      throw new QueryException($insert_result);
    }

    return $this->concreteModelFactory->extrudeWithId(
      new UnsignedInt($insert_result->lastInsertId()),
      $params
    );
  }
}
