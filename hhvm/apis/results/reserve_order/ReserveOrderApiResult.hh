<?hh // strict

class ReserveOrderApiResult extends SuccessfulApiResult {

  const string ID_KEY = "id";

  public function __construct(
    private UnsignedInt $id
  ) {
    parent::__construct(ApiType::RESERVE_ORDER);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::ID_KEY => $this->id->getNumber(),
    };
  }
}
