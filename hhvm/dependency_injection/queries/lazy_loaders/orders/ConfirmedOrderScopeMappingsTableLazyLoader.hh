<?hh // strict

class ConfirmedOrderScopeMappingsTableLazyLoader extends LazyLoader<ConfirmedOrderScopeMappingsTable> {

  protected function make(): ConfirmedOrderScopeMappingsTable {
    return new ConfirmedOrderScopeMappingsTable();
  }
}
