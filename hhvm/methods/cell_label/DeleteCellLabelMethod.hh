<?hh // strict

class DeleteCellLabelMethod {

  public function __construct(
    private DeleteByIdQuery<CellLabel> $deleteByIdQuery,
  ) {}

  public function delete(UnsignedInt $id): void {
    try {
      // Attempt to delete cell label
      $this->deleteByIdQuery
        ->delete($id)
        ->getWaitHandle()
        ->join();
       
    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    } 
  }
}
