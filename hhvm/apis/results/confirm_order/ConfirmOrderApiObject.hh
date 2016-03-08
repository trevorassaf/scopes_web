<?hh // strict

class ConfirmOrderApiObject {

  const string ID_KEY = 'id';
  const string SCOPES_COUNT_KEY = 'scopes-count';
  const string START_TIME_KEY = 'start';
  const string END_TIME_KEY = 'end';
  const string TITLE_KEY = 'title';
  const string DESCRIPTION_KEY = 'description';
  const string TIME_ORDERED_KEY = 'time-ordered';
  const string PRICE_KEY = "price";
  const string SHORT_CODE_KEY = 'short-code';

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $scopesCount,
    private string $startTime,
    private string $endTime,
    private ?string $title,
    private ?string $description,
    private string $timeOrdered,
    private UnsignedFloat $price,
    private ShortCodeApiObject $shortCode
  ) {}

  public function getResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::ID_KEY => $this->id->getNumber(),
      self::SCOPES_COUNT_KEY => $this->scopesCount->getNumber(),
      self::START_TIME_KEY => $this->startTime,
      self::END_TIME_KEY => $this->endTime,
      self::TITLE_KEY => $this->title,
      self::DESCRIPTION_KEY => $this->description,
      self::PRICE_KEY => $this->price->getNumber(),
      self::TIME_ORDERED_KEY => $this->timeOrdered,
      self::SHORT_CODE_KEY => $this->shortCode->getResultFields(),
    };
  }
}
