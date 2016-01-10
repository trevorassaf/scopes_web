<?hh // strict

class ConfirmedOrderScopeMappingsTable extends Table {
  
  const string TABLE_NAME = "ConfirmedOrderScopeMappings";
  const string CONFIRMED_ORDER_ID_KEY = "confirmedOrderId";
  const string VIRTUAL_SCOPE_INDEX_KEY = "virtualScopeIndex";
  const string PHYSICAL_SCOPE_INDEX_KEY = "physicalScopeIndex";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getConfirmedOrderIdKey(): string {
    return self::CONFIRMED_ORDER_ID_KEY;
  }

  public function getVirtualScopeIndexKey(): string {
    return self::VIRTUAL_SCOPE_INDEX_KEY; 
  }

  public function getPhysicalScopeIndexKey(): string {
    return self::PHYSICAL_SCOPE_INDEX_KEY;
  }
}
