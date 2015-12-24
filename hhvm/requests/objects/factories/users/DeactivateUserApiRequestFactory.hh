<?hh // strict

class DeactivateUserApiRequestFactory implements RequestFactory<DeactivateUserApiRequest> {

  private RequestFieldFactory<UnsignedInt> $userIdFieldFactory;

  public function __construct() {
    // Create user id field factory
    $user_id_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $this->userIdFieldFactory = $user_id_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): DeactivateUserApiRequest {
    $deactivate_user_request_builder = new DeactivateUserApiRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case DeactivateUserApiRequest::USER_ID_KEY:
          $deactivate_user_request_builder->setUserId(
            $this->userIdFieldFactory->make($key, $value)
          );
          break;
        default:
          throw new UnexpectedRequestFieldKeyException(__CLASS__, $key);
          break;
      }
    }
    return $deactivate_user_request_builder->build();
  }

}
