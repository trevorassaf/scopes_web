<?hh // strict

class BasicVideoDownloadReceiptModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<BasicVideoDownloadReceipt>> {

  public function __construct(
    private LazyLoader<BasicVideoDownloadReceiptsTable> $basicVideoDownloadReceiptsTableLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializer
  ) {}

  protected function make(): ConcreteModelFactory<BasicVideoDownloadReceipt> {
    return new BasicVideoDownloadReceiptFactory(
      $this->basicVideoDownloadReceiptsTableLoader->load(),
      $this->timestampSerializer->load()
    );
  }
}
