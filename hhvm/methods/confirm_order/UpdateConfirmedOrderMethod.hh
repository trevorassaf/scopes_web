<?hh // strict

class UpdateConfirmedOrderMethod {

  public function __construct(
    private UpdateByIdQuery $updateQuery,
    private ConfirmedOrdersTable $table
  ) {}

  public function update(
    UpdateConfirmedOrderRequest $request
  ): void {
    // Put update fields in map
    $update_field_map = Map{};

    $title_field = $request->getTitle();
    if ($title_field !== null) {
      $update_field_map[$this->table->getTitleKey()] = $title_field->get();
    }

    $description_field = $request->getDescription();
    if ($description_field !== null) {
      $update_field_map[$this->table->getDescriptionKey()] = $description_field->get();
    }

    $short_code_field = $request->getShortCode();
    if ($short_code_field !== null) {
      $update_field_map[$this->table->getShortCodeIdKey()] = $short_code_field->get();
    }

    // Update confirmed order object with provided fields
    try {
      $this->updateQuery
        ->update(
          $this->table,
          $update_field_map->toImmMap(),
          $request->getConfirmedOrderId()->get()
        )
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    } 
  }
}
