<?hh // strict

class GetStartupDataApiResult extends SuccessfulApiResult {

  const string FIRST_NAME_KEY = "first_name";
  const string LAST_NAME_KEY = "last_name";
  const string EMAIL_KEY = "email";
  const string HOURLY_PRICE_KEY = "hourly_price";
  const string USER_SHORT_CODES_KEY = "short_codes";

  public function __construct(
    private string $firstName,
    private string $lastName,
    private Email $email,
    private UnsignedFloat $hourlyPrice,
    private ImmVector<ShortCodeApiObject> $shortCodes
  ) {
    parent::__construct(ApiType::GET_STARTUP_DATA);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    // Package short codes for transport
    $short_code_data = Vector{};
    foreach ($this->shortCodes as $short_code) {
      $short_code_data[] = $short_code->getResultFields();
    }

    return ImmMap{
      self::FIRST_NAME_KEY => $this->firstName,
      self::LAST_NAME_KEY => $this->lastName,
      self::EMAIL_KEY => $this->email->toString(),
      self::HOURLY_PRICE_KEY => $this->hourlyPrice->getNumber(),
      self::USER_SHORT_CODES_KEY => $short_code_data->toImmVector(),
    };
  }
}
