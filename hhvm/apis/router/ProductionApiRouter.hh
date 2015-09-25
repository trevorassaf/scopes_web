<?hh // strict

class ProductionApiRouter implements ApiRouter {

  public function __construct(
    private ApiInjector $apiInjector
  ) {}

  public function route(
    ApiType $type,
    ImmMap<string, mixed> $raw_request_fields
  ): ApiResult {

ob_start();
var_dump($type);
var_dump($raw_request_fields);
$contents = ob_get_contents();
ob_end_clean();
error_log("ProductionApiRouter::route()");
error_log($contents);

    // Perform route based on api-type
    $api = null;

    switch ($type) {
      case ApiType::CREATE_USER:
        $api = $this->apiInjector->getCreateUserApi();
        break;
      case ApiType::GET_USER:
        $api = $this->apiInjector->getGetUserByEmailApi();
        break;
      case ApiType::RESERVE_ORDER:
        $api = $this->apiInjector->getReserveOrderApi();
        break;
      case ApiType::CONFIRM_ORDER:
        $api = $this->apiInjector->getConfirmOrderApi();
        break;
      case ApiType::UPDATE_CONFIRMED_ORDER:
        $api = $this->apiInjector->getUpdateConfirmedOrderApi();
        break;
      default:
        // TODO return failed result
        break;
    }    

    invariant($api !== null, "can't be null...");

    return $api->processRequest($raw_request_fields);
  }
}
