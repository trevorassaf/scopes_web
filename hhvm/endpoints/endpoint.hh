<?hh // decl 

function main(): void {
  $api_runner_factory = new DebugApiRunnerFactory();
  $http_server = new HttpServer(
    $api_runner_factory,
    new HttpParamsFetcher()
  );
  $http_server->run();
}

main();
