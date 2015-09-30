<?hh // strict

class FetchQuery<Tmodel> {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private ModelFactory<Tmodel> $modelFactory,
    private QueryExceptionFactory $queryExceptionFactory
  ) {} 

  public async function fetch(
    FetchQueryMaker $query_maker
  ): Awaitable<ImmVector<Tmodel>> {
    // Serialize fetch query
    $query_str = $query_maker->serialize();
    
//var_dump($query_str);

    try {
      // Execute fetch query
      $result_set = await $this->asyncMysqlConnection->query($query_str);
      
      // Extrude query results
      $field_map_set = $result_set->mapRowsTyped();
      
      $objects = Vector{};
      foreach ($field_map_set as $field_map) {
        $objects[] = $this->modelFactory->extrude($field_map->toImmMap());
      }

      return $objects->toImmVector();

    } catch (AsyncMysqlQueryException $ex) {
      throw $this->queryExceptionFactory->make($ex);
    }
  }
}
