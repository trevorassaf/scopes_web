<?hh // strict

abstract class AsyncMysqlConnectionFactory {

  public async function get(): Awaitable<AsyncMysqlConnection> {
    $connection_config = $this->getConnectionConfig();
    
    return await AsyncMysqlClient::connect(
      $connection_config->getIpAddress(),
      $connection_config->getPort(),
      $connection_config->getDbName(),
      $connection_config->getUsername(),
      $connection_config->getPassword()
    );
  }

  abstract protected function getConnectionConfig(): ConnectionConfig;
}
