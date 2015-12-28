<?hh // strict

class GetUsersReservedOrdersApi extends Api<GetUsersReservedOrdersApiRequest> {

  public function __construct(
    RequestFactory<GetUsersReservedOrdersApiRequest> $request_factory,
    private GetUsersReservedOrdersMethod $getUsersReservedOrdersMethod,
    private Logger $logger,
    private HRTimestampSerializer $timestampSerializer
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  protected function processRequestObject(
    GetUsersReservedOrdersApiRequest $request
  ): ApiResult {
    try {
      // Fetch user's reserved orders
      $user_id = $request->getUserId()->get();

      $rsvd_orders = $this->getUsersReservedOrdersMethod->get(
        $user_id
      ); 

      // Convert to api result objects
      $rsvd_order_api_objects = Vector{};
      foreach ($rsvd_orders as $order) {
        $rsvd_order_api_objects[] = new ReservedOrderApiObject(
          $order->getId()->getNumber(),
          $order->getScopesCount()->getNumber(),
          $this->timestampSerializer->serialize(
            $order->getTimestampSegment()->getStart()
          ), 
          $this->timestampSerializer->serialize(
            $order->getTimestampSegment()->getEnd()
          )
        );
      }

      return new GetUsersReservedOrdersApiResult(
        $rsvd_order_api_objects->toImmVector()
      );

    } catch (NonextantObjectException $ex) {
      return new FailedGetUsersReservedOrdersApiResult(
        FailedGetUsersReservedOrdersApiResultType::NONEXTANT_USER
      );
    }
  }

  public function getApiType(): ApiType {
    return ApiType::GET_USERS_RSVD_ORDERS;
  }
}
