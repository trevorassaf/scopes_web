<?hh // strict

class Gen0OrderPricePolicyModelFactory extends ConcreteModelFactory<Gen0OrderPricePolicy> {

  public function __construct(
    private TimestampSerializer $timestampSerializer,
    private Gen0OrderPricePoliciesTable $table
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $param_map
  ): Gen0OrderPricePolicy {
    return new Gen0OrderPricePolicy(
      $id,
      $this->timestampSerializer->deserialize((string)$param_map[$this->table->getTimeEnactedKey()]),
      new UnsignedFloat((float)$param_map[$this->table->getPriceKey()]),
    );  
  }
}
