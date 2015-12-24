<?hh // strict

class DeactivateUserApiRequest {

  const string REQUEST_OBJECT_NAME = "DeactivateUser";
  const string USER_ID_KEY = "id";

  public function __construct(
    private RequestField<UnsignedInt> $userId
  ) {}

  public function getUserId(): RequestField<UnsignedInt> {
    return $this->userId;
  }
}

class DeactivateUserApiRequestBuilder {

  private ?RequestField<UnsignedInt> $id;

  public function setUserId(
    RequestField<UnsignedInt> $user_id
  ): this {
    $this->id = $user_id;
    return $this;
  }

  public function build(): DeactivateUserApiRequest {
    // Check for missing user-id key
    if ($this->id === null) {
      throw new UnsetRequestFieldException(
        DeactivateUserApiRequest::REQUEST_OBJECT_NAME,
        DeactivateUserApiRequest::USER_ID_KEY
      );
    }

    return new DeactivateUserApiRequest($this->id);
  }
}
