<?hh // strict

class UpdateCellLabelMethod {

  public function __construct(
    private UpdateByIdQuery $updateQuery,
    private CellLabelsTable $table
  ) {}

  public function update(
    ImmMap<string, mixed> $update_params,
    UnsignedInt $id
  ): void {
    try {
      $this->updateQuery
        ->update(
          $this->table,
          $update_params,
          $id
        )
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {} 
  }
}
