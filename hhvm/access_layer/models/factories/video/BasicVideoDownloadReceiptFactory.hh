<?hh // strict

class BasicVideoDownloadReceiptFactory extends ConcreteModelFactory<BasicVideoDownloadReceipt> {

  public function __construct(
    private BasicVideoDownloadReceiptsTable $table,
    private HRTimestampSerializer $timestampSerializer
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): BasicVideoDownloadReceipt {
    return new BasicVideoDownloadReceipt(
      $id,
      new UnsignedInt((int)$params[$this->table->getBasicVideoIdKey()]),
      $this->timestampSerializer->deserialize((string)$params[$this->table->getDownloadTimeKey()])
    );
  }
}
