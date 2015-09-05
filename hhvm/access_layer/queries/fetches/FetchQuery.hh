<?hh // strict

class FetchQuery<Tmodel> {

  const string WHERE_CONDITION_LIST_DELIMITER = ", ";

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private Table<Tmodel> $table 
  ) {} 

  public async function fetchAll(): Awaitable<ImmVector<Tmodel>> {
    return await $this->executeFetchQuery(
      $this->createFetchAllQuery()
    );
  }

  public async function fetch(
    WhereClause $where_clause
  ): Awaitable<ImmVector<Tmodel>> {
    return await $this->executeFetchQuery(
      $this->createFetchQuery($where_clause)
    );
  }

  private async function executeFetchQuery(
    string $fetch_query
  ): Awaitable<ImmVector<Tmodel>> {
    $result_set = await $this->asyncMysqlConnection->query($fetch_query);
    $field_map_set = $result_set->mapRowsTyped();
    $objects = Vector{};
    foreach ($field_map_set as $field_map) {
      $objects[] = $this->table->extrude($field_map->toImmMap());
    }
    return $objects->toImmVector();
  }

  private function createFetchAllQuery(): string {
    return "SELECT * FROM " . $this->table->getTableName();
  }

  public function getTable(): Table<Tmodel> {
    return $this->table;
  }

  private function createFetchQuery(
    WhereClause $where_clause
  ): string {
    return
      "SELECT * FROM " . $this->table->getTableName()
      . " WHERE " . $where_clause->serialize();
  }
}
