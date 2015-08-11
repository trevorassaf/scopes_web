<?hh // strict

class Database {

  private DbConfig $config;
  private ?AsyncMysqlConnection $connection;

  public function __construct(
    DbConfig $config
  ) {
    $this->config = $config;
    $this->connection = null;
  }

  public function open(): void {}
  public function close(): void {}

}
