<?hh // strict

class CompletedOrdersTableLazyLoader extends LazyLoader<CompletedOrdersTable> {

  protected function make(): CompletedOrdersTable {
    return new CompletedOrdersTable();
  }
}
