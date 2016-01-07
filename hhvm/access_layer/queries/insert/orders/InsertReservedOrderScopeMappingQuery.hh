<?hh // strict

class InsertReservedOrderScopeMappingQuery {

  public function __construct(
    private InsertQuery<ReservedOrderScopeMapping> $insertQuery,
    private ReservedOrderScopeMappingsTable $table
  ) {}

  public async function insert(
    UnsignedInt $rsvd_order_id,
    UnsignedInt $virtual_scope_idx,
    UnsignedInt $physical_scope_idx 
  ): Awaitable<ReservedOrderScopeMapping> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->table->getReservedOrderIdKey() => $rsvd_order_id->getNumber(),
        $this->table->getVirtualScopeIndexKey() => $virtual_scope_idx->getNumber(),
        $this->table->getPhysicalScopeIndexKey() => $physical_scope_idx->getNumber(),
      }
    );
  }
}
