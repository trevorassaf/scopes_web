<?hh // decl

require_once(dirname(__FILE__).'/../vendor/autoload.php');

function main(): void {
  
  // Endpoint settings 
  date_default_timezone_set("America/Los_Angeles");
  error_reporting(E_ALL); 

  // Initialize api runner factory
  $api_runner_factory = new DevApiRunnerFactory();

  // Start http server
  $http_server = new HttpServer(
    $api_runner_factory->make(),
    new HttpParamsFetcher(),
    $api_runner_factory->getLogger()
  );

  $http_server->run();
}

main();
