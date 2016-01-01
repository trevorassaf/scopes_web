<?hh // decl

require_once(dirname(__FILE__).'/../vendor/autoload.php');

function main(): void {
  
  // Endpoint settings 
  date_default_timezone_set("America/Los_Angeles");
  error_reporting(E_ALL); 

  $logger_factory = new LocalLoggerFactory();
  $logger = $logger_factory->make();

  $production_api_runner_factory = new ProductionApiRunnerFactory(
    $logger
  );

  // Start http server
  $http_server = new HttpServer(
    $production_api_runner_factory->make(),
    new HttpParamsFetcher(),
    $logger
  );

  $http_server->run();
}

main();
