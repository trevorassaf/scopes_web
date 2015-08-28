<?hh // strict

class HttpServer {

  public function __construct(
    private ApiRunner $apiRunner,
    private HttpParamsFetcher $httpParamsFetcher
  ) {}

  public function run(): void {
    $http_params = $this->httpParamsFetcher->fetch();
    echo $this->apiRunner->run($http_params);
  }
}
