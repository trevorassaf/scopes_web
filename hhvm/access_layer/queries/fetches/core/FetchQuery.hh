<?hh // strict

class FetchQuery<Tmodel> {

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection
  ) {} 

  public async function fetch(
    FetchParams $fetch_params
  ): Awaitable<ImmVector<Tmodel>> {
    // Execute query
    $result_set = await $this->asyncMysqlConnection
      ->query(
        $fetch_params->serialize()
      );

    // Extrude query results
    $field_map_set = $result_set->mapRowsTyped();
    $objects = Vector{};
    foreach ($field_map_set as $field_map) {
      $objects[] = $this->table->extrude($field_map->toImmMap());
    }
    return $objects->toImmVector();
  }

  public function getTable(): Table<Tmodel> {
    return $this->table;
  }
}
