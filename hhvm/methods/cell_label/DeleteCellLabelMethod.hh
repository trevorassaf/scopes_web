<?hh // strict

class DeleteCellLabelMethod {

  public function __construct(
    private DeleteByIdQuery $deleteByIdQuery,
    private CellLabelsTable $cellLabelsTable
  ) {}

  public function delete(UnsignedInt $id): void {
    try {
      // Attempt to delete cell label
      $is_deleted = $this->deleteByIdQuery
        ->delete(
          $this->cellLabelsTable,
          $id
        )
        ->getWaitHandle()
        ->join();

      // If no row was deleted, then 'id' does not correspond
      // to existing cell-label
      if (!$is_deleted) {
        throw new NonextantObjectException();
      }
       
    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    } 
  }
}
