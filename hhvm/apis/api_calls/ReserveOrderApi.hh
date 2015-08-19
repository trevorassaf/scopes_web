<?hh // strict

class ReserveOrderApi implements Api {

  const USER_ID_KEY = "user-id";
  const SCOPES_COUNT_KEY = "scopes-count";
  const START_TIME_KEY = "start-time";
  const RESERVED_MINUTES_COUNT = "rsvd-min-count";

  public function __construct(
    private WebParamsFetcher $webParamsFetcher,
    private SerializerFactory $serializerFactory,
    private ApiExceptionToApiResultErrorConverter $apiExceptionToApiResultErrorConverter,
    private ReserveOrderMethod $reserveOrderMethod    
  ) {}

  public function processRequest(): ApiResult {
    return $this->addOrderToUser(
      $this->webParamsFetcher->fetchPostParam(self::USER_ID_KEY),
      $this->webParamsFetcher->fetchPostParam(self::SCOPES_COUNT_KEY),
      $this->webParamsFetcher->fetchPostParam(self::START_TIME_KEY),
      $this->webParamsFetcher->fetchPostParam(self::RESERVED_MINUTES_COUNT)
    ); 
  }

  public function addOrderToUser(
    string $user_id,
    string $scopes_count,
    string $start_time,
    string $rsvd_min_count
  ): ApiResult {
    // Validate parameters against api-specific requirements
    try {
      $this->validateParameters(
        $user_id,
        $scopes_count,
        $start_time,
        $rsvd_min_count
      );
    } catch (ApiException $ex) {
      return $this
        ->apiExceptionToApiResultErrorConverter
        ->convert($ex);
    }

    // Data passed api checks, so attempt
    // db write. May still receive error
    // from db layer...
    try {
      $order = $this->reserveOrderMethod->reserve(
        new UnsignedInt((int)$user_id),
        new UnsignedInt((int)$scopes_count),
        new Timestamp($start_time),
        new UnsignedInt((int)$rsvd_min_count),
        OrderStatusType::RESERVED
      );
      
      // Order added successfully, return data to client...
      return new ReserveOrderApiResult(
        $this->serializerFactory,
        $order
      );
    } catch (ApiException $ex) {
      return $this
        ->apiExceptionToApiResultErrorConverter
        ->convert($ex);
    }
  }

  public function validateParameters(
    string $user_id,
    string $scopes_count,
    string $start_time,
    string $rsvd_min_count
  ): void {
    
  }

  public function validateUserId(string $user_id): void {}
}
