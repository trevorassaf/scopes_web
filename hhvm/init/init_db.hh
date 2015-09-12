<?hh // strict

require_once(dirname(__FILE__).'/../vendor/autoload.php');

function initDbMain(): void {
  // Set server timezone
  date_default_timezone_set("America/Detroit");

  // Block for connection to mysql db 
  $db_factory = new ProductionAsyncMysqlConnectionFactory();
  $async_mysql_connection = $db_factory
    ->get()
    ->getWaitHandle()
    ->join();
  
}

initDbMain();
