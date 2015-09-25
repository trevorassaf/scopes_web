<?hh // strict

class UpdateCellLabelMethod {

  public function __construct(
    private UpdateByIdQuery $updateQuery,
    private CellLabelsTable $table
  ) {}

  public function update(
    UpdateCellLabelRequest $request
  ): void {
    // Place update fields in map
    $update_field_map = ImmMap{
      $this->table->getLabelKey() => $request->getLabel()->get(),
    };

    // Update cell label object with new label
    try {
      $this->updateQuery->update(
        $this->table,
        $update_field_map,
        $request->getCellLabelId()->get()
      )
      ->getWaitHandle()
      ->join(); 
    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);    
    }
  }
}
