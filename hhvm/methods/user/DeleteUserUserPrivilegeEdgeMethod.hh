<?hh // strict

class DeleteUserUserPrivilegeEdgeMethod {

  public function __construct(
    private FetchByIdQuery<UserUserPrivilegeEdge> $fetchEdgeQuery,
    private DeleteByIdQuery $deleteByIdQuery,
    private UserUserPrivilegeEdgesTable $edgeTable
  ) {}

  public function delete(UnsignedInt $edge_id): void {
    try {
      // Check to see if edge exists 
      $fetch_query = $this->fetchEdgeQuery->fetch($edge_id);

      $edge = $fetch_query
        ->getWaitHandle()
        ->join();

      if ($edge === null) {
        throw new NonextantObjectException();
      }

      // Delete edge
      $delete_handle = $this->deleteByIdQuery->delete(
        $this->edgeTable,
        $edge_id
      ); 

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
