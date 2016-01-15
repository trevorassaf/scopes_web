<?hh // strict

class GetSessionInfoApi extends Api<GetSessionInfoApiRequest> {

  public function __construct(
    RequestFactory<GetSessionInfoApiRequest> $request_factory,
    private Logger $logger 
  ) {
    parent::__construct(
      $request_factory,
      $this->logger
    );
  }

  public function getApiType(): ApiType {
    return ApiType::GET_SESSION_INFO;
  }

  protected function processRequestObject(
    UserAgent $user_agent,
    GetSessionInfoApiRequest $get_session_info_request
  ): ApiResult {
    return new GetSessionInfoApiResult(
      new UnsignedInt(1),
      "Trevor",
      "Assaf",
      new Email("astrev@umich.edu")
    ); 
  }
}
