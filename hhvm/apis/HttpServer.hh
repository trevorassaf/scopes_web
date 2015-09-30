<?hh // strict

class HttpServer {

  public function __construct(
    private ApiRunner $apiRunner,
    private HttpParamsFetcher $httpParamsFetcher,
    private Logger $logger
  ) {}

  public function run(): void {
    // Obtain get/post web params
    $http_params = $this->httpParamsFetcher->fetch();

    // Pass http params to api-router
    $result_str = $this->apiRunner->run($http_params);

    // Log response object
    $this->logger->info("Response string: " . $result_str);

    // Return result message to user
    echo $result_str;
  }
}
