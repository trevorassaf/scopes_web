<?hh // strict

class ReservedOrderScopeMappingFactory extends ConcreteModelFactory<ReservedOrderScopeMapping> {

  public function __construct(
    private ReservedOrderScopeMappingsTable $reservedOrderScopeMappingsTable
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): ReservedOrderScopeMapping {
    return new ReservedOrderScopeMapping(
      $id,
      new UnsignedInt((int)$params[$this->reservedOrderScopeMappingsTable->getReservedOrderIdKey()]),
      new UnsignedInt((int)$params[$this->reservedOrderScopeMappingsTable->getVirtualScopeIndexKey()]),
      new UnsignedInt((int)$params[$this->reservedOrderScopeMappingsTable->getPhysicalScopeIndexKey()]),
    );
  }
}
