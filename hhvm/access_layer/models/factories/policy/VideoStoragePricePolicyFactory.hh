<?hh // strict

class VideoStoragePricePolicyFactory implements ModelFactory<VideoStoragePricePolicy> {

  public function __construct(
    private TimestampSerializer $timestampSerializer,
    private VideoStoragePricePolicyTable $table,
  ) {}

  public function extrude(ImmMap<string, mixed> $param_map): VideoStoragePricePolicy {
    return new VideoStoragePricePolicy(
      new UnsignedFloat((float)$param_map[$this->table->getPriceKey()]),
      $this->timestampSerializer->deserialize((string)$param_map[$this->table->getTimeEnactedKey()]),
      new UnsignedInt((int)$param_map[$this->table->getNumberFreeDaysKey()])
    );  
  }
}
