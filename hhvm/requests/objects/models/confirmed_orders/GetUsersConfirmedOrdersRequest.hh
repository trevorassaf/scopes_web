<?hh // strict

class GetUsersConfirmedOrdersRequest {

  const string REQUEST_OBJECT_NAME = "GetUsersConfirmedOrdersRequest";

  const string USER_ID_KEY = "uid";

  public function __construct(
    private RequestField<UnsignedInt> $userIdOrderId
  ) {}

  public function getUserId(): RequestField<UnsignedInt> {
    return $this->userIdOrderId;
  }
}

class GetUsersConfirmedOrdersRequestBuilder {
  
  private ?RequestField<UnsignedInt> $userId;

  public function setUserId(RequestField<UnsignedInt> $user_id): this {
    $this->userId = $user_id;
    return $this;
  }

  public function build(): GetUsersConfirmedOrdersRequest {
    if ($this->userId === null) {
      throw new UnsetRequestFieldException(
        GetUsersConfirmedOrdersRequest::REQUEST_OBJECT_NAME, 
        GetUsersConfirmedOrdersRequest::USER_ID_KEY
      );
    }
    return new GetUsersConfirmedOrdersRequest($this->userId);
  }
}
