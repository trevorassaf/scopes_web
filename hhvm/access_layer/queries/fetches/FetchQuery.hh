<?hh // strict

class FetchQuery<Tmodel> {

  const string WHERE_CONDITION_LIST_DELIMITER = ", ";

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private Table<Tmodel> $table 
  ) {} 

  public async function fetchAll(): Awaitable<ImmVector<Tmodel>> {
    $result_set = await $this->asyncMysqlConnection->query(
      $this->createFetchAllQuery()
    ); 
    return $this->extrudeResultMap($result_set->mapRowsTyped());
  }

  public async function fetch(WhereClause $where_clause): Awaitable<ImmVector<Tmodel>> {
    $result_set = await $this->asyncMysqlConnection->query(
      $this->createFetchQuery($where_clause)
    );
  }

  private function extrudeResultMap(
    ImmMap<string, mixed> $field_map_set
  ): ImmVector<Tmodel> {
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
