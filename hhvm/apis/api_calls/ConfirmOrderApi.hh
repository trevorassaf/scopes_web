<?hh // strict

class ConfirmOrderApi implements Api {

  const USER_ID_KEY = "user-id";
  const SCOPES_COUNT_KEY = "scopes-count";
  const START_TIME_KEY = "start-time";
  const RESERVED_MINUTES_COUNT = "rsvd-min-count";

  public function __construct(
    private WebParamsFetcher $webParamsFetcher,
    private ConfirmOrderMethod $confirmOrderMethod    
  ) {}

  public function processRequest(): ApiResult {
    $this->confirmOrder(
      $this->webParamsFetcher->fetchPostParam(self::USER_ID_KEY),
      $this->webParamsFetcher->fetchPostParam(self::SCOPES_COUNT_KEY),
      $this->webParamsFetcher->fetchPostParam(self::START_TIME_KEY),
      $this->webParamsFetcher->fetchPostParam(self::RESERVED_MINUTES_COUNT)
    ); 
    return new EmptyApiResult();
  }

  public function confirmOrder(
    string $user_id,
    string $scopes_count,
    string $start_time,
    string $rsvd_min_count
  ): void {
    // Validate parameters against api-specific requirements

    // Data passed api checks, so attempt
    // db write. May still receive error
    // from db layer...
    try {
      $this->confirmOrderMethod->confirm(
        new UnsignedInt((int)$user_id)
      );
      
      // Order added successfully, return data to client...
    } catch (ApiException $ex) {}
  }
}
