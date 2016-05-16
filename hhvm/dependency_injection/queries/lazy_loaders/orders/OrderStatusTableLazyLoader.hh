<?hh // strict

class OrderStatusTableLazyLoader extends LazyLoader<OrderStatusTable> {

  protected function make(): OrderStatusTable {
    return new OrderStatusTable();
  }
}
