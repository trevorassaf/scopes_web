<?hh // strict

class BatchInsertQuery<Tmodel> {

  public function __construct(
      private AsyncMysqlConnection $asyncMysqlConnection,
      private Table<Tmodel> $table,
      private InsertQueryCreater $insertQueryCreater
  ) {}

  public async function insert(
    ImmVector<ImmMap<string, mixed>> $model_field_maps
  ): Awaitable<ImmVector<Tmodel>> {
    $objects = Vector{}; 

    foreach ($model_field_maps as $field_map) {
      $insert_handle = await $this->asyncMysqlConnection->query(
        $this->insertQueryCreater->createQuery(
          $this->table->getTableName(),
          $field_map
        )
      );
    }

    return $objects->toImmVector();
  }
}
