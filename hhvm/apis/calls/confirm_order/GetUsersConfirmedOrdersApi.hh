<?hh // strict

class GetUsersConfirmedOrdersApi extends Api<GetUsersConfirmedOrdersRequest> {

  public function __construct(
    RequestFactory<GetUsersConfirmedOrdersRequest> $request_factory,
    private GetUsersConfirmedOrdersMethod $getUsersConfirmedOrdersMethod,
    private Logger $logger,
    private TimestampSerializer $timestampSerializer
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    UserAgent $user_agent,
    GetUsersConfirmedOrdersRequest $request
  ): ApiResult {
    // Log get users confirmed order api call
    $this->logger->info("Get user's confirmed orders api call...");

    try {
      // Fetch confirmed orders w/cell-label
      $confirmed_orders_list = $this->getUsersConfirmedOrdersMethod
        ->get($request->getUserId()->get());

      // Prepare data to send back to client
      $confirmed_order_api_object_list = Vector{};

      foreach ($confirmed_orders_list as $confirmed_order) {
        $confirmed_order_api_object_list[] = new ConfirmOrderApiObject(
          $confirmed_order->getId()->getNumber(),
          $confirmed_order->getScopesCount()->getNumber(),
          $this->timestampSerializer->serialize($confirmed_order->getTimestampSegment()->getStart()),
          $this->timestampSerializer->serialize($confirmed_order->getTimestampSegment()->getEnd()),
          $confirmed_order->getTitle(),
          $confirmed_order->getDescription(),
          $this->timestampSerializer->serialize($confirmed_order->getTimeOrdered())
        );
      }

      return new GetUsersConfirmedOrdersApiResult(
        $confirmed_order_api_object_list->toImmVector()
      );

    } catch (NonextantObjectException $ex) {
      // Log that requested user does not exist!
      $this->logger->info("Requested user does not exist!");
      return new FailedGetUsersConfirmedOrdersApiResult(
        FailedGetUsersConfirmedOrdersApiResultType::NONEXTANT_USER 
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::GET_USERS_CONFIRMED_ORDERS;
  }
}
