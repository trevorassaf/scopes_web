<?hh // strict

class InsertOrderPricePolicyQuery {

  public function __construct(
    private InsertQuery<OrderPricePolicy> $insertQuery,
    private OrderPricePolicyTable $orderPricePolicyTable,
    private HRTimestampSerializer $hrTimestampSerializer
  ) {}

  public async function insert(
    UnsignedFloat $price,
    Timestamp $time_enacted 
  ): Awaitable<OrderPricePolicy> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->orderPricePolicyTable->getPriceKey() => $price->getNumber(),
        $this->orderPricePolicyTable->getTimeEnactedKey() => $this->hrTimestampSerializer->serialize($time_enacted),
      }
    );    
  }
}
