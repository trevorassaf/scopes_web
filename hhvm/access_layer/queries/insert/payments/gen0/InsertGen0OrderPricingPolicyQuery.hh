<?hh // strict

class InsertGen0OrderPricePolicyQuery {

  public function __construct(
    private InsertQuery<Gen0OrderPricePolicy> $insertQuery,
    private Gen0OrderPricePoliciesTable $table,
    private HRTimestampSerializer $timestampSerializer
  ) {}

  public async function insert(
    Timestamp $time_enacted,
    UnsignedFloat $price
  ): Awaitable<Gen0OrderPricePolicy> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->table->getTimeEnactedKey() => $this->timestampSerializer->serialize($time_enacted),
        $this->table->getPriceKey() => $price->getNumber(),
      }
    );
  }
}
