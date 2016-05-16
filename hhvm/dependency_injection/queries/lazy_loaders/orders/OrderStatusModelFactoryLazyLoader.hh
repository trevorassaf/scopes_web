<?hh // strict

class OrderStatusModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<OrderStatus>> {

  public function __construct(
    private OrderStatusTableLazyLoader $tableLoader
  ) {}

  protected function make(): ConcreteModelFactory<OrderStatus> {
    return new OrderStatusModelFactory(
      $this->tableLoader->load()
    );
  }
}
