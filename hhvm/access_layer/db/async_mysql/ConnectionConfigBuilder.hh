<?hh // strict

class ConnectionConfigBuilder {

  private ?string $ipAddress;
  private ?int $port;
  private ?string $dbName;
  private ?string $username;
  private ?string $password;

  public function setIpAddress(string $ip_address): this {
    $this->ipAddress = $ip_address;
    return $this;
  }

  public function setPort(int $port): this {
    $this->port = $port;
    return $this;
  }

  public function setDbName(string $db_name): this {
    $this->dbName = $db_name;
    return $this;
  }

  public function setUsername(string $username): this {
    $this->username = $username;
    return $this;
  }

  public function setPassword(string $password): this {
    $this->password = $password;
    return $this;
  }

  public function build(): ConnectionConfig {
    invariant($this->ipAddress !== null, "Ip address cannot be null!");
    invariant($this->port !== null, "Port cannot be null!");
    invariant($this->dbName !== null, "Db name cannot be null!");
    invariant($this->username !== null, "Username cannot be null!");
    invariant($this->password !== null, "Password cannot be null!");

    return new ConnectionConfig(
      $this->ipAddress,
      $this->port,
      $this->dbName,
      $this->username,
      $this->password
    );
  }
}
