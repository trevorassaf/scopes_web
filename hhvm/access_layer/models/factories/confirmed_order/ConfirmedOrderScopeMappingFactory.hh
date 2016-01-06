<?hh // strict

class ConfirmedOrderScopeMappingFactory extends ConcreteModelFactory<ConfirmedOrderScopeMapping> {
  
  public function __construct(
    private ConfirmedOrderScopeMappingsTable $confirmedOrderScopeMappingsTable
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): ConfirmedOrderScopeMapping {
    return new ConfirmedOrderScopeMapping(
      $id,
      new UnsignedInt((int)$params[$this->confirmedOrderScopeMappingsTable->getConfirmedOrderIdKey()]),
      new UnsignedInt((int)$params[$this->confirmedOrderScopeMappingsTable->getVirtualScopeIndexKey()]),
      new UnsignedInt((int)$params[$this->confirmedOrderScopeMappingsTable->getPhysicalScopeIndexKey()]),
    );
  }

}
