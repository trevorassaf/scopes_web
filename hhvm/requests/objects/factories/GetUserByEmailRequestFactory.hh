<?hh // strict

class GetUserByEmailRequestFactory implements RequestFactory<GetUserByEmailRequest> {

  public function __construct(
    private RequestFieldFactory<Email> $emailFieldFactory
  ) {}

  public function make(ImmMap<string, mixed> $raw_field_map): GetUserByEmailRequest {
    $get_user_by_email_request_builder = new GetUserByEmailRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case GetUserByEmailRequest::EMAIL_KEY:
          $get_user_by_email_request_builder->setEmail(
            $this->emailFieldFactory->make($key, $value)
          );
          break;
        default:
          throw new InvalidRequestFieldKeyException(__CLASS__, $key);
          break;
      }
    }

    return $get_user_by_email_request_builder->build();
  }
}
