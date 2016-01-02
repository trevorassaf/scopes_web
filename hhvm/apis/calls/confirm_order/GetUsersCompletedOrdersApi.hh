<?hh // strict

class GetUsersCompletedOrdersApi extends Api<GetUsersCompletedOrdersApiRequest> {

  public function __construct(
    RequestFactory<GetUsersCompletedOrdersApiRequest> $request_factory,
    private GetUsersCompletedOrdersMethod $getUsersCompletedOrdersMethod,
    private Logger $logger,
    private HRTimestampSerializer $timestampSerializer
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    UserAgent $user_agent,
    GetUsersCompletedOrdersApiRequest $request
  ): ApiResult {
    // Log get user's completed orders call  
    $this->logger->info("Get user's completed orders api call...");

    // Fetch user's completed orders
    try {
      $completed_orders = $this->getUsersCompletedOrdersMethod->get(
        $request->getUserId()->get()
      ); 

      // Repackage CompletedOrders data for return to client
      $api_object_list = Vector{};
      foreach ($completed_orders as $order) {
        $api_object_list[] = new CompletedOrderApiObject(
          $order->getId()->getNumber(),
          $this->timestampSerializer->serialize($order->getTimeCompleted()),
          $order->getConfirmedOrderId()->getNumber()
        );
      }

      return new GetUsersCompletedOrdersApiResult(
        $api_object_list->toImmVector()
      );

    } catch (NonextantObjectException $ex) {
      $this->logger->info("User does not exist!");
      return new FailedGetUsersCompletedOrdersApiResult(
        FailedGetUsersCompletedOrdersApiResultType::NONEXTANT_USER
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::GET_USERS_COMPLETED_ORDERS;
  }
}
