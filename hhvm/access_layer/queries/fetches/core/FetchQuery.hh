<?hh // strict

class FetchQuery<Tmodel> {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private ModelFactory<Tmodel> $modelFactory
  ) {} 

  public async function fetch(
    FetchQueryMaker $query_maker
  ): Awaitable<ImmVector<Tmodel>> {
    // Serialize fetch query
    $query_str = $query_maker->serialize();
    
var_dump($query_str);

    // Execute fetch query
    $result_set = await $this->asyncMysqlConnection->query($query_str);

    // Check if query failed
    if ($result_set instanceof AsyncMysqlQueryErrorResult) {
      throw new QueryException($result_set); 
    }

    // Extrude query results
    $field_map_set = $result_set->mapRowsTyped();
    
    $objects = Vector{};
    foreach ($field_map_set as $field_map) {
      $objects[] = $this->modelFactory->extrude($field_map->toImmMap());
    }
    return $objects->toImmVector();
  }
}
