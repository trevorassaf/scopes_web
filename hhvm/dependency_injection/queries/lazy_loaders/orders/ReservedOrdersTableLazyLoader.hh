<?hh // strict

class ReservedOrdersTableLazyLoader extends LazyLoader<RsvdOrdersTable> {

  protected function make(): RsvdOrdersTable {
    return new RsvdOrdersTable();
  }
}
