<?hh // strict

class GetStartupDataApiResult extends SuccessfulApiResult {

  const string FIRST_NAME_KEY = "first-name";
  const string LAST_NAME_KEY = "last-name";
  const string EMAIL_KEY = "email";
  const string HOURLY_PRICE_KEY = "hourly-price";

  public function __construct(
    private string $firstName,
    private string $lastName,
    private Email $email,
    private UnsignedFloat $hourlyPrice
  ) {
    parent::__construct(ApiType::GET_STARTUP_DATA);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::FIRST_NAME_KEY => $this->firstName,
      self::LAST_NAME_KEY => $this->lastName,
      self::EMAIL_KEY => $this->email->toString(),
      self::HOURLY_PRICE_KEY => $this->hourlyPrice->getNumber(),
    };
  }
}
