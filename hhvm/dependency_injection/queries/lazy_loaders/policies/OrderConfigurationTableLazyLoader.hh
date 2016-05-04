<?hh // strict

class OrderConfigurationTableLazyLoader extends LazyLoader<OrderConfigurationTable> {

  protected function make(): OrderConfigurationTable {
    return new OrderConfigurationTable();
  }
}
