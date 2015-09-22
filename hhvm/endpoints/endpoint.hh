<?hh // decl

require_once(dirname(__FILE__).'/../vendor/autoload.php');

function main(): void {
  
  // Endpoint settings 
  date_default_timezone_set("America/Detroit");
  error_reporting(E_ALL); 
  
  $production_api_runner_factory = new ProductionApiRunnerFactory();
  $http_server = new HttpServer(
    $production_api_runner_factory->make(),
    new HttpParamsFetcher()
  );
  $http_server->run();
}

main();
