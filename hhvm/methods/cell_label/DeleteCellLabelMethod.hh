<?hh // strict

class DeleteCellLabelMethod {

  public function __construct(
    private DeleteByIdQuery $deleteByIdQuery,
    private CellLabelsTable $cellLabelsTable
  ) {}

  public function delete(UnsignedInt $id): void {
    try {
      // Attempt to delete cell label
      $this->deleteByIdQuery
        ->delete(
          $this->cellLabelsTable,
          $id
        )
        ->getWaitHandle()
        ->join();
       
    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    } 
  }
}
