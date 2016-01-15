<?hh // strict

class GetSessionInfoApiResult extends SuccessfulApiResult {

  const string USER_ID_KEY = "uid";
  const string USER_FIRST_NAME_KEY = "first-name";
  const string USER_LAST_NAME_KEY = "last-name";
  const string USER_EMAIL_KEY = "email";

  public function __construct(
    private UnsignedInt $userId,
    private string $firstName,
    private string $lastName,
    private Email $email
  ) {
    parent::__construct(ApiType::GET_SESSION_INFO);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::USER_ID_KEY => $this->userId->getNumber(),
      self::USER_FIRST_NAME_KEY => $this->firstName,
      self::USER_LAST_NAME_KEY => $this->lastName,
      self::USER_EMAIL_KEY => $this->email->toString(),
    };
  }
}
