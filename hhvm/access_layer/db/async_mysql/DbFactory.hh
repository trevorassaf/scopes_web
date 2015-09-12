<?hh // strict

interface DbFactory {

  public async function get(): Awaitable<AsyncMysqlConnection>;
}
