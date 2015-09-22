<?hh // decl

function main(): void {
  error_reporting(E_ALL); 
  
  $production_api_runner_factory = new ProductionApiRunnerFactory();
  $http_server = new HttpServer(
    $production_api_runner_factory->make(),
    new HttpParamsFetcher()
  );
  $http_server->run();
}

main();
