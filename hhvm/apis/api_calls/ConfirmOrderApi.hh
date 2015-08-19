<?hh // strict

class ConfirmOrderApi implements Api {

  const string RSVD_ORDER_KEY = "ro-id"; 
  const string TITLE_KEY = "title";
  const string DESCRIPTION_KEY = "desc";
  const string SHORT_CODE_KEY = "short-code";
  const string RECORDING_DURATION_KEY = "rec-duration";

  public function __construct(
    private WebParamsFetcher $webParamsFetcher,
    private ConfirmOrderMethod $confirmOrderMethod    
  ) {}

  public function processRequest(): ApiResult {
    $this->confirmOrder(
      $this->webParamsFetcher->fetchPostParam(self::RSVD_ORDER_KEY),
      $this->webParamsFetcher->fetchPostParam(self::TITLE_KEY),
      $this->webParamsFetcher->fetchPostParam(self::DESCRIPTION_KEY),
      $this->webParamsFetcher->fetchPostParam(self::SHORT_CODE_KEY),
      $this->webParamsFetcher->fetchPostParam(self::RECORDING_DURATION_KEY)
    ); 
    return new EmptyApiResult();
  }

  public function confirmOrder(
    string $user_id,
    string $title,
    string $description,
    string $short_code,
    string $recording_duration
  ): void {
    // Validate parameters against api-specific requirements

    // Data passed api checks, so attempt
    // db write. May still receive error
    // from db layer...
    try {
      $this->confirmOrderMethod->confirm(
        new UnsignedInt((int)$user_id),
        $title,
        $description,
        $short_code,
        $recording_duration
      );
      
      // Order added successfully, return data to client...
    } catch (ApiException $ex) {}
  }
}
