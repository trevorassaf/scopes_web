<?hh // strict

class ConnectionConfig {

  public function __construct(
    private string $ipAddress,
    private int $port,
    private string $dbName,
    private string $username,
    private string $password
  ) {}

  public function getIpAddress(): string {
    return $this->ipAddress;
  }

  public function getPort(): int {
    return $this->port;
  }

  public function getDbName(): string {
    return $this->dbName;
  }

  public function getUsername(): string {
    return $this->username;
  }

  public function getPassword(): string {
    return $this->password;
  }
}
