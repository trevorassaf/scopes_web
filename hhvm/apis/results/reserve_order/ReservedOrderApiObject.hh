<?hh // strict

class ReservedOrderApiObject {

  const string RESERVED_ORDER_ID_KEY = "id";
  const string SCOPES_COUNT_KEY = "scopes-count";
  const string START_TIME_KEY = "start-time";
  const string END_TIME_KEY = "end-time";

  public function __construct(
    private int $rsvdOrderId,
    private int $scopesCount,
    private string $startTime,
    private string $endTime
  ) {}

  public function getResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::RESERVED_ORDER_ID_KEY => $this->rsvdOrderId,
      self::SCOPES_COUNT_KEY => $this->scopesCount,
      self::START_TIME_KEY => $this->startTime,
      self::END_TIME_KEY => $this->endTime,
    };
  }
}
