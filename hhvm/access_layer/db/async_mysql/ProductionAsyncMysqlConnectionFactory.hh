<?hh // strict

class ProductionAsyncMysqlConnectionFactory extends AsyncMysqlConnectionFactory {

  protected function getConnectionConfig(): ConnectionConfig {
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
