<?hh // strict

class GetStartupDataApiResult extends SuccessfulApiResult {

  const string FIRST_NAME_KEY = "first_name";
  const string LAST_NAME_KEY = "last_name";
  const string EMAIL_KEY = "email";
  const string HOURLY_PRICE_KEY = "hourly_price";
  const string USER_SHORT_CODES_KEY = "short_codes";
  const string MAX_NUM_SCOPES = 'max_scopes';
  const string MAX_EXPERIMENT_DURATION = 'max_hours';
  const string START_TIME_KEY = 'start-time';
  const string END_TIME_KEY = 'end-time';
  const string START_TIME_INTERVAL_KEY = 'start-time-interval';
  const string MIN_DAYS_IN_ADVANCE_KEY = 'min-days-in-advance';
  const string MAX_MONTHS_IN_ADVANCE_KEY = 'max-months-in-advance';
  const string DISALLOWED_DATES_KEY = 'disallowed-dates';
  const string DISALLOWED_WEEK_DAYS_KEY = 'disallowed-week-days';

  public function __construct(
    private string $firstName,
    private string $lastName,
    private Email $email,
    private UnsignedFloat $hourlyPrice,
    private ImmVector<ShortCodeApiObject> $shortCodes,
    private UnsignedInt $maxScopes,
    private UnsignedInt $maxHours,
    private TimeApiObject $startTime,
    private TimeApiObject $endTime,
    private UnsignedInt $startTimeInterval,
    private UnsignedInt $minDaysInAdvance,
    private UnsignedInt $maxMonthsInAdvance,
    private ImmVector<DateApiObject> $disallowedDates,
    private ImmVector<UnsignedInt> $disallowedWeekDays
  ) {
    parent::__construct(ApiType::GET_STARTUP_DATA);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    // Package short codes for transport
    $short_code_data = Vector{};
    foreach ($this->shortCodes as $short_code) {
      $short_code_data[] = $short_code->getResultFields();
    }

    // Package disallowed dates for transport
    $disallowed_dates_data = Vector{};
    foreach ($this->disallowedDates as $date) {
      $disallowed_dates_data[] = $date->getResultFields();
    }

    // Package disallowed days of the week for transport
    $disallowed_week_days_data = Vector{};
    foreach ($this->disallowedWeekDays as $day) {
      $disallowed_week_days_data[] = $day->getNumber();
    }

    return ImmMap{
      self::FIRST_NAME_KEY => $this->firstName,
      self::LAST_NAME_KEY => $this->lastName,
      self::EMAIL_KEY => $this->email->toString(),
      self::HOURLY_PRICE_KEY => $this->hourlyPrice->getNumber(),
      self::USER_SHORT_CODES_KEY => $short_code_data->toImmVector(),
      self::MAX_NUM_SCOPES => $this->maxScopes->getNumber(),
      self::MAX_EXPERIMENT_DURATION => $this->maxHours->getNumber(),
      self::START_TIME_KEY => $this->startTime->getResultFields(),
      self::END_TIME_KEY => $this->endTime->getResultFields(),
      self::START_TIME_INTERVAL_KEY => $this->startTimeInterval->getNumber(),
      self::MIN_DAYS_IN_ADVANCE_KEY => $this->minDaysInAdvance->getNumber(),
      self::MAX_MONTHS_IN_ADVANCE_KEY => $this->maxMonthsInAdvance->getNumber(),
      self::DISALLOWED_DATES_KEY => $disallowed_dates_data->toImmVector(),
      self::DISALLOWED_WEEK_DAYS_KEY => $disallowed_week_days_data->toImmVector(),
    };
  }
}
