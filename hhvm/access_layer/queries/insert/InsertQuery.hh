<?hh // strict

class InsertQuery<Tmodel> {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private Table $table,
    private ConcreteModelFactory<Tmodel> $concreteModelFactory,
    private InsertQueryCreater $insertQueryCreater,
    private QueryExceptionFactory $queryExceptionFactory
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

    try {
      // Execute insert query
      $insert_result = await $this->asyncMysqlConnection->query($query_str); 
      
      return $this->concreteModelFactory->extrudeWithId(
        new UnsignedInt($insert_result->lastInsertId()),
        $params
      );
    } catch (AsyncMysqlQueryException $ex) {
      throw $this->queryExceptionFactory->make($ex);
    }
  }
}
