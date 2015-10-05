<?hh // strict

class GetUserByUniqueKeyApiResult extends SuccessfulApiResult {
  
  const string ID_KEY = "id";
  const string FIRST_NAME_KEY = "first-name";
  const string LAST_NAME_KEY = "last-name";
  const string EMAIL_KEY = "email";

  public function __construct(
    private ApiType $api_type,   
    private User $user
  ) {
    parent::__construct($api_type);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::ID_KEY => $this->user->getId()->getNumber(),
      self::FIRST_NAME_KEY => $this->user->getFirstName(),
      self::LAST_NAME_KEY => $this->user->getLastName(),
      self::EMAIL_KEY => $this->user->getEmail()->toString(),
    };
  }
}
