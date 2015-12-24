<?hh // strict

class DeleteUsersShortCodesMethod {

  public function __construct(
    private FetchByIdQuery<User> $fetchUserByIdQuery,
    private DeleteQuery $deleteShortCodesQuery,
    private ShortCodeTable $shortCodesTable
  ) {}

  public function delete(UnsignedInt $user_id): void {
    // Check that the user exists
    $fetch_handle = $this->fetchUserByIdQuery->fetch($user_id);

    $user = $fetch_handle
      ->getWaitHandle()
      ->join();

    if ($user === null) {
      throw new NonextantObjectException();  
    }

    // Delete all short codes owned by this user
    $where_clause_builder = new WhereClauseVectorBuilder();     
    $where_clause_builder->setFirstClause(
      new EqualsWhereClause(
        $this->shortCodesTable->getUserIdKey(),
        $user_id
      )
    );

    $delete_handle = $this->deleteShortCodesQuery->delete(
      $this->shortCodesTable,
      $where_clause_builder->build()
    );

    $delete_handle->getWaitHandle()->join();
  }
}
