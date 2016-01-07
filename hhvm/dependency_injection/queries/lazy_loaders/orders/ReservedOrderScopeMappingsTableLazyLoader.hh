<?hh // strict

class ReservedOrderScopeMappingsTableLazyLoader extends LazyLoader<ReservedOrderScopeMappingsTable> {

  protected function make(): ReservedOrderScopeMappingsTable {
    return new ReservedOrderScopeMappingsTable();
  }
}
