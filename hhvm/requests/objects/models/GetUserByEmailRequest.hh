<?hh // strict

class GetUserByEmailRequest {

  const string EMAIL_KEY = "email";

  public function __construct(
    private RequestField<Email> $email
  ) {}

  public function getEmail(): RequestField<Email> {
    return $this->email;
  }
}

class GetUserByEmailRequestBuilder {

  private ?RequestField<Email> $email;

  public function setEmail(
    RequestField<Email> $email
  ): this {
    $this->email = $email;
    return $this;
  }

  public function build(): GetUserByEmailRequest {
    // Check for missing request keys
    if ($this->email == null) {
      throw UnsetRequestFieldException(RequestWrapper::EMAIL_KEY);
    }

    // Extrude request object
    return new GetUserByEmailRequest(
      $this->email
    );
  }
}
