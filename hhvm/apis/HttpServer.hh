<?hh // strict

class HttpServer {

  public function __construct(
    private ApiRunner $apiRunner,
    private HttpParamsFetcher $httpParamsFetcher
  ) {}

  public function run(): void {
    $http_params = $this->httpParamsFetcher->fetch();
    $result_str = $this->apiRunner->run($http_params);

error_log("HttpServer::run() result string:\n");
error_log($result_str);

    echo $result_str;
  }
}
