<?hh // strict

class DeleteUsersFutureConfirmedOrdersMethod {

  public function __construct(
    private FetchByIdQuery<User> $fetchUserByIdQuery,
    private DeleteQuery $deleteQuery,
    private ConfirmedOrdersTable $confirmedOrdersTable,
    private TimestampBuilder $timestampBuilder,
    private HRTimestampSerializer $timestampSerializer
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

      // Delete all rsvd orders associated with this user that
      // have not yet occurred
      $current_time = $this->timestampBuilder->now();
      
      $where_clause_vector_builder = new WhereClauseVectorBuilder(); 
      $where_clause_vector_builder
        ->setFirstClause(
          new EqualsWhereClause(
            $this->confirmedOrdersTable->getUserIdKey(),
            $user_id->getNumber()
          )
        )
        ->logicalAnd(
          new GreaterThanWhereClause(
            $this->confirmedOrdersTable->getStartTimeKey(),
            $this->timestampSerializer->serialize($current_time)
          )
        );

      $delete_handle = $this->deleteQuery->delete(
        $this->confirmedOrdersTable,
        $where_clause_vector_builder->build()
      );

      $delete_handle->getWaitHandle()->join();

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
