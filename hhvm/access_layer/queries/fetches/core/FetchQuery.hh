<?hh // strict

class FetchQuery<Tmodel> {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private ModelFactory<Tmodel> $modelFactory
  ) {} 

  public async function fetch(
    FetchQueryMaker $query_maker
  ): Awaitable<ImmVector<Tmodel>> {
    // Execute query
    $result_set = await $this->asyncMysqlConnection
      ->query(
        $query_maker->serialize()
      );

    // Extrude query results
    $field_map_set = $result_set->mapRowsTyped();
    $objects = Vector{};
    foreach ($field_map_set as $field_map) {
      $objects[] = $this->modelFactory->extrude($field_map->toImmMap());
    }
    return $objects->toImmVector();
  }
}
