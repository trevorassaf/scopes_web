<?hh // strict

class ProductionApiRouter implements ApiRouter {

  public function __construct(
    private ApiInjector $apiInjector,
    private Logger $logger
  ) {}

  public function route(
    ApiType $type,
    ImmMap<string, mixed> $raw_request_fields
  ): ApiResult {
    // Log api type 
    $this->logger->info("Routing api request", $type);
    $this->logger->info("Request payload", $raw_request_fields);

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
      case ApiType::UPDATE_CELL_LABEL:
        $api = $this->apiInjector->getUpdateCellLabelApi(); 
        break;
      case ApiType::DELETE_CELL_LABEL:
        $api = $this->apiInjector->getDeleteCellLabelApi();
        break;
      case ApiType::DELETE_CONFIRMED_ORDER:
        $api = $this->apiInjector->getDeleteConfirmedOrderApi();
        break;
      case ApiType::DELETE_RESERVED_ORDER:
        $api = $this->apiInjector->getDeleteReservedOrderApi();
        break;
      case ApiType::GET_USERS_CONFIRMED_ORDERS:
        $api = $this->apiInjector->getGetUsersConfirmedOrdersApi();
        break;
      case ApiType::UPLOAD_BASIC_VIDEOS:
        $api = $this->apiInjector->getUploadBasicVideoApi();
        break;
      case ApiType::UPLOAD_EDITED_VIDEO:
        $api = $this->apiInjector->getUploadEditedVideoApi();
        break;
      case ApiType::COMPLETE_ORDER:
        $api = $this->apiInjector->getCompleteOrderApi();
        break;
      case ApiType::GET_ALL_USERS:
        $api = $this->apiInjector->getGetAllUsersApi();
        break;
      default:
        throw new Exception("Unhandled api type!");
        break;
    }

    invariant($api !== null, "api can't be null...");

    return $api->processRequest($raw_request_fields);
  }
}
