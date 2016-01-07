<?hh // strict

class InsertConfirmedOrderScopeMappingQuery {

  public function __construct(
    private InsertQuery<ConfirmedOrderScopeMapping> $insertQuery,
    private ConfirmedOrderScopeMappingsTable $table
  ) {}

  public async function insert(
    UnsignedInt $confirmed_order_id,
    UnsignedInt $virtual_scope_idx,
    UnsignedInt $physical_scope_idx 
  ): Awaitable<ConfirmedOrderScopeMapping> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->table->getConfirmedOrderIdKey() => $confirmed_order_id->getNumber(),
        $this->table->getVirtualScopeIndexKey() => $virtual_scope_idx->getNumber(),
        $this->table->getPhysicalScopeIndexKey() => $physical_scope_idx->getNumber(),
      }
    );
  }
}
