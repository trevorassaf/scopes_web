<?hh // strict

class ProductionDbFactory implements DbFactory {

  private static ?AsyncMysqlConnection $connection;

  public async function get(): Awaitable<AsyncMysqlConnection> {
    if (self::$connection === null) {
      self::$connection = await $this->initConnection();
    }
    return self::$connection;
  }

  private async function initConnection(): Awaitable<AsyncMysqlConnection> {
    $connection_config = $this->getConnectionConfig();
    return await AsyncMysqlClient::connect(
      $connection_config->getIpAddress(),
      $connection_config->getPort(),
      $connection_config->getDbName(),
      $connection_config->getUsername(),
      $connection_config->getPassword()
    ); 
  }

  private function getConnectionConfig(): ConnectionConfig {
    $connection_config_builder = new ConnectionConfigBuilder();
    return $connection_config_builder
      ->setIpAddress("127.0.0.1")
      ->setPort(3306)
      ->setDbName("Scopes")
      ->setUsername("trevor")
      ->setPassword("password")
      ->build();
  }
}
