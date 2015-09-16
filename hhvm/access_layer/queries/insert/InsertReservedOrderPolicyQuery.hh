<?hh // strict

class InsertReservedOrderPolicyQuery {

  public function __construct(
    private InsertQuery<ReservedOrderPolicy> $insertQuery,
    private ReservedOrderPolicyTable $table
  ) {}

  public async function insert(
    UnsignedInt $scopes_count
  ): Awaitable<ReservedOrderPolicy> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->table->getScopesCountKey() => $scopes_count->getNumber(),
      }
    );
  }
}
