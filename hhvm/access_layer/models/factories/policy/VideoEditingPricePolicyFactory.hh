<?hh // strict

class VideoEditingPricePolicyFactory implements ModelFactory<VideoEditingPricePolicy> {

  public function __construct(
    private TimestampSerializer $timestampSerializer,
    private VideoEditingPricePolicyTable $table
  ) {}
  
  public function extrude(ImmMap<string, mixed> $param_map): VideoEditingPricePolicy {
    return new VideoEditingPricePolicy(
      new UnsignedFloat((float)$param_map[$this->table->getPriceKey()]),
      $this->timestampSerializer->deserialize((string)$param_map[$this->table->getTimeEnactedKey()])
    );  
  }
}
