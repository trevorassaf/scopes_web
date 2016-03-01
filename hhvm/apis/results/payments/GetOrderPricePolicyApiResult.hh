<?hh // strict

class GetOrderPricePolicyApiResult extends SuccessfulApiResult {

  const string PRICE_KEY = "price"; 

  public function __construct(
    private UnsignedFloat $price
  ) {
    parent::__construct(ApiType::GET_ORDER_PRICE_POLICY);
  }

  protected function getCustomResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::PRICE_KEY => $this->price->getNumber(),
    };
  }
}
