<?hh // strict

class AsyncMysqlConnectionLazyLoader extends LazyLoader<AsyncMysqlConnection> {

  public function __construct(
    private AsyncMysqlConnectionFactory $factory
  ) {}

  protected function make(): AsyncMysqlConnection {
    $connection = $this->factory->get();
    return $connection->getWaitHandle()->join();
  }
}
