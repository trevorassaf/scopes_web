<?hh // strict

class GetAllUsersMethod {

  public function __construct(
    private FetchQuery<User> $fetchUsersQuery,
    private UsersTable $usersTable
  ) {}

  public function get(): ImmVector<User> {
    // Fetch all users  
    try {
      // Build vacuous where/order-by clause
      $where_clause_vector_builder = new WhereClauseVectorBuilder();
      $order_by_clause_builder = new OrderByClauseBuilder();
      $fetch_users_handle = $this->fetchUsersQuery->fetch(
        new FetchParams(
          $this->usersTable,
          $where_clause_vector_builder->build(),
          $order_by_clause_builder->build()
        ) 
      );

      return $fetch_users_handle
        ->getWaitHandle()
        ->join();

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    } 
  }
}
