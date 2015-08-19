<?hh // strict

class ReserveOrderApi implements Api {

  const string USER_ID_KEY = "user-id";
  const string LEASE_START_KEY = "lease-start";
  const string SCOPES_COUNT_KEY = "scopes-count";
  const string START_TIME_KEY = "start-time";
  const string RESERVED_MINUTES_COUNT = "rsvd-min-count";

  public function __construct(
    private WebParamsFetcher $webParamsFetcher,
    private ReserveOrderMethod $reserveOrderMethod    
  ) {}

  public function processRequest(): ApiResult {
    $this->reserveOrder(
      $this->webParamsFetcher->fetchPostParam(self::USER_ID_KEY),
      $this->webParamsFetcher->fetchPostParam(self::LEASE_START_KEY),
      $this->webParamsFetcher->fetchPostParam(self::SCOPES_COUNT_KEY),
      $this->webParamsFetcher->fetchPostParam(self::START_TIME_KEY),
      $this->webParamsFetcher->fetchPostParam(self::RESERVED_MINUTES_COUNT)
    ); 
    return new EmptyApiResult();
  }

  public function reserveOrder(
    string $user_id,
    string $lease_start,
    string $scopes_count,
    string $start_time,
    string $rsvd_min_count
  ): void {
    // Validate parameters against api-specific requirements
    
    // Data passed api checks, so attempt
    // db write. May still receive error
    // from db layer...
    try {
      $this->reserveOrderMethod->reserve(
        new UnsignedInt((int)$user_id),
        new Timestamp($lease_start),
        new UnsignedInt((int)$scopes_count),
        new Timestamp($start_time),
        new UnsignedInt((int)$rsvd_min_count)
      );
      
      // Order added successfully, return data to client...
    } catch (ApiException $ex) {
    }
  }
}
