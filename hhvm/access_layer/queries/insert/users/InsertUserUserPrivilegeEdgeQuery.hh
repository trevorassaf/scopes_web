<?hh // strict

class InsertUserUserPrivilegeEdgeQuery {

  public function __construct(
    private InsertQuery<UserUserPrivilegeEdge> $insertQuery,
    private UserUserPrivilegeEdgesTable $table
  ) {}

  public async function insert(
    UnsignedInt $user_id,
    UnsignedInt $user_privilege_id
  ): Awaitable<UserUserPrivilegeEdge> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->table->getUserIdKey() => $user_id->getNumber(),
        $this->table->getUserPrivilegeIdKey() => $user_privilege_id->getNumber(),
      }
    );
  }
}
