<?hh // strict

class FetchUsersPrivilegesQuery {

  public function __construct(
    private FetchQuery<UserUserPrivilegeEdge> $fetchUserUserPrivilegeEdgesQuery,
    private UserUserPrivilegeEdgesTable $userUserPrivilegeEdgesTable
  ) {}

  public async function fetch(
    UnsignedInt $user_id
  ): Awaitable<ImmVector<UserPrivilege>> {
    $fetch_params_builder = new FetchParamsBuilder(); 

    // Where clause: all privileges associated with this user
    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $fetch_params_builder->setWhereClause(
      $where_clause_vector_builder->setFirstClause(
        new EqualsWhereClause(
          $this->userUserPrivilegeEdgesTable->getUserIdKey(),
          $user_id->getNumber()
        )
      )
      ->build()
    );

    // Execute fetch query
    $user_privilege_edges = await $this->fetchUserUserPrivilegeEdgesQuery->fetch(
      $fetch_params_builder
        ->setTable($this->userUserPrivilegeEdgesTable)
        ->build()
    );

    // Convert user-privilege edges to UserPrivilege list
    $user_privilege_list = Vector{};
    
    foreach ($user_privilege_edges as $edge) {
      $user_privilege_list[] = new UserPrivilege(
        $edge->getUserPrivilegeId()
      );   
    }

    return $user_privilege_list->toImmVector();
  }
}
