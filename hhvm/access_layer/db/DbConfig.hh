<?hh

class DbConfig {

  public function __construct(
      private string $dbName,
      private string $username,
      private string $password
  ) {}

  public function getDbName(): string {
    return $this->dbName;
  }

  public function getUserName(): string {
    return $this->username;
  }

  public function getPassword(): string {
    return $this->password;
  }
}
