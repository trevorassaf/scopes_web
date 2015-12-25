<?hh // strict

class DeleteUsersRsvdOrdersMethod {

  public function __construct(
    private FetchByIdQuery<User> $fetchUserByIdQuery,
    private DeleteQuery $deleteQuery,
    private RsvdOrdersTable $rsvdOrdersTable
  ) {}

  public function delete(UnsignedInt $user_id): void {
    try {
      // Check that user exists
      $fetch_handle = $this->fetchUserByIdQuery->fetch($user_id);

      $user = $fetch_handle
        ->getWaitHandle()
        ->join();

      if ($user === null) {
        throw new NonextantObjectException();
      }

      // Delete all rsvd orders associated with this user
      $where_clause_vector_builder = new WhereClauseVectorBuilder(); 
      $where_clause_vector_builder->setFirstClause(
        new EqualsWhereClause(
          $this->rsvdOrdersTable->getUserIdKey(),
          $user_id->getNumber()
        )
      );

      $delete_handle = $this->deleteQuery->delete(
        $this->rsvdOrdersTable,
        $where_clause_vector_builder->build()
      );

      $delete_handle->getWaitHandle()->join();

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
