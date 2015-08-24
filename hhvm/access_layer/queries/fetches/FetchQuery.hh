<?hh // strict

class FetchQuery<Tmodel> {

  const string WHERE_CONDITION_LIST_DELIMITER = ", ";

  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private Table<Tmodel> $table 
  ) {} 

  public async function fetch(
    ImmMap<string, mixed> $params 
  ): Awaitable<ImmVector<Tmodel>> {
    $result_set = await $this->asyncMysqlConnection->query(
      $this->createQuery($params)
    ); 

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

  private function createQuery(
    ImmMap<string, mixed> $params
  ): string {
    return
      "SELECT FROM " . $this->table->getTableName()
      . " WHERE " . $this->createWhereClauseCondition($params);
  }

  private function createWhereClauseCondition(
    ImmMap<string, mixed> $params
  ): string {
    $where_clause_condition = "";  
    foreach ($params as $key => $value) {
      $where_clause_condition .=
        $key . "='" . (string)$value . "'"
        . self::WHERE_CONDITION_LIST_DELIMITER;
    }
    return substr(
      $where_clause_condition,
      0,
      strlen($where_clause_condition) - strlen(self::WHERE_CONDITION_LIST_DELIMITER)
    );
  }
}
