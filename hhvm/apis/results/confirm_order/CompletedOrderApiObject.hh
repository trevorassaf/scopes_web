<?hh // strict

class CompletedOrderApiObject {

  const string ID_KEY = "id";
  const string TIME_COMPLETED_KEY = "time-completed";
  const string CONFIRMED_ORDER_ID_KEY = "confirmed-order-id";

  public function __construct(
    private int $id,
    private string $timeCompleted,
    private int $confirmedOrderId 
  ) {}

  public function getResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::ID_KEY => $this->id,
      self::TIME_COMPLETED_KEY => $this->timeCompleted,
      self::CONFIRMED_ORDER_ID_KEY => $this->confirmedOrderId,
    }; 
  }
}
