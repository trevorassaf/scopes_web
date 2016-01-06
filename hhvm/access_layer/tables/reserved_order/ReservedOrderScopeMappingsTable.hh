<?hh // strict

class ReservedOrderScopeMappingsTable extends Table {
  
  const string TABLE_NAME = "ReservedOrderScopeMappings";
  const string RSVD_ORDER_ID_KEY = "rsvdOrderId";
  const string VIRTUAL_SCOPE_INDEX_KEY = "virtualScopeIndex";
  const string PHYSICAL_SCOPE_INDEX_KEY = "physicalScopeIndex";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getReservedOrderIdKey(): string {
    return self::RSVD_ORDER_ID_KEY;
  }

  public function getVirtualScopeIndexKey(): string {
    return self::VIRTUAL_SCOPE_INDEX_KEY; 
  }

  public function getPhysicalScopeIndexKey(): string {
    return self::PHYSICAL_SCOPE_INDEX_KEY;
  }
}
