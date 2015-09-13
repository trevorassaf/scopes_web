<?hh // strict

require_once(dirname(__FILE__).'/../vendor/autoload.php');

function initDbMain(): void {
  // Set server timezone
  date_default_timezone_set("America/Detroit");

}

initDbMain();
