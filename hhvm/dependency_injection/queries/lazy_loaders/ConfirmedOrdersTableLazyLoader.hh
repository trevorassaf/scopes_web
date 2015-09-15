<?hh // strict

class ConfirmedOrdersTableLazyLoader extends LazyLoader<ConfirmedOrdersTable> {

  protected function make(): ConfirmedOrdersTable {
    return new ConfirmedOrdersTable();
  }
}
