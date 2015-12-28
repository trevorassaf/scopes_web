<?hh // strict

class GetUsersCompletedOrdersApiRequest {

  const string REQUEST_OBJECT_NAME = "GetUsersCompletedOrdersApiRequest";
  const string USER_ID_KEY = "uid";

  public function __construct(
    private RequestField<UnsignedInt> $userId
  ) {}

  public function getUserId(): RequestField<UnsignedInt> {
    return $this->userId;
  }
}

class GetUsersCompletedOrdersApiRequestBuilder {

  private ?RequestField<UnsignedInt> $userId;

  public function setUserId(RequestField<UnsignedInt> $user_id): this {
    $this->userId = $user_id;
    return $this;
  }

  public function build(): GetUsersCompletedOrdersApiRequest {
    if ($this->userId === null) {
      throw new UnsetRequestFieldException(
        GetUsersCompletedOrdersApiRequest::REQUEST_OBJECT_NAME,
        GetUsersCompletedOrdersApiRequest::USER_ID_KEY
      );
    }

    return new GetUsersCompletedOrdersApiRequest(
      $this->userId
    );
  }
}
