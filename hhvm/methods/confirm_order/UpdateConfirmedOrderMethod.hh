<?hh // strict

class UpdateConfirmedOrderMethod {

  public function __construct(
    private UpdateByIdQuery $updateQuery,
    private ConfirmedOrdersTable $table
  ) {}

  public function update(
    UpdateConfirmedOrderRequest $request
  ): void {
    // TODO Check validity of fields 
    $title = $request->getTitle();
    $description = $request->getDescription();
    $short_code_id = $request->getShortCodeId();

    // Put update fields in map
    $update_field_map = Map{};

    if ($title !== null) {
      $update_field_map[$this->table->getTitleKey()] = $title;
    }

    if ($description !== null) {
      $update_field_map[$this->table->getDescriptionKey()] = $description;
    }

    if ($short_code_id !== null) {
      $update_field_map[$this->table->getShortCodeIdKey()] = $short_code_id;
    }

    // Update confirmed order object with provided fields
    try {
      $this->updateQuery
        ->update(
          $this->table,
          $update_field_map->toImmMap(),
          $request->getConfirmedOrderId()
        )
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    } 
  }
}
