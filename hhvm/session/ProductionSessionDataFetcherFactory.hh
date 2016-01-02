<?hh // strict

class ProductionSessionDataFetcherFactory {

  public function __construct(
    private Logger $logger,
    private HRTimestampSerializer $timestampSerializer
  ) {}

  public function get(): ProductionSessionDataFetcher {
    return new ProductionSessionDataFetcher(
      new RawSessionDataFetcher(),
      $this->logger,
      $this->timestampSerializer,
      new SessionKeys()
    ); 
  }
}
