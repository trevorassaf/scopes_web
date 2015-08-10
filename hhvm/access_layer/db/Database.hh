<?hh // strict

class Database {

  private DbConfig $config;
  private bool $isOpen;
  private bool $isTransaction;


  public function __construct(
    DbConfig $config
  ) {
    $this->config = $config;
    $this->isOpen = false;
    $this->isTransaction = false;
  }

  public function beginTxn(): void {}
  public function endTxn(): void {}
  public function open(): void {}
  public function close(): void {}

}
