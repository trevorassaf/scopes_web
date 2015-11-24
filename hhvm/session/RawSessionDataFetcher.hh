<?hh // strict

class RawSessionDataFetcher {

  public function fetch(): ImmMap<string, mixed> {
    // UNSAFE
    return new ImmMap($_SESSION);
  }
}
