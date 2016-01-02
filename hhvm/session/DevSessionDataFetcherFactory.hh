<?hh // strict

class DevSessionDataFetcherFactory {

  public function __construct(
    private TimestampBuilder $timestampBuilder
  ) {}

  public function get(): DevSessionDataFetcher {
    return new DevSessionDataFetcher($this->timestampBuilder);    
  }
}
