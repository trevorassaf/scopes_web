<?hh // strict

class SessionManager {

  public function __construct(
    private SessionDataFetcher $sessionReader,
    private RawSessionDataWriter $sessionWriter
  ) {}
}
