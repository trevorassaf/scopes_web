<?hh // strict

class GetUsersReservedOrdersApiRequest {

  const string REQUEST_OBJECT_NAME = "GetUsersReservedOrdersApiRequest";
  const string USER_ID_KEY = "uid";

  public function __construct(
    private RequestField<UnsignedInt> $userId
  ) {}

  public function getUserId(): RequestField<UnsignedInt> {
    return $this->userId;
  }
}

class GetUsersReservedOrdersApiRequestBuilder {
  
  private ?RequestField<UnsignedInt> $userId;

  public function setUserId(RequestField<UnsignedInt> $user_id): this {
    $this->userId = $user_id;
    return $this;
  }

  public function build(): GetUsersReservedOrdersApiRequest {
    if ($this->userId === null) {
      throw new UnsetRequestFieldException(
        GetUsersReservedOrdersApiRequest::REQUEST_OBJECT_NAME,
        GetUsersReservedOrdersApiRequest::USER_ID_KEY
      );
    }
    return new GetUsersReservedOrdersApiRequest($this->userId);
  }
}
