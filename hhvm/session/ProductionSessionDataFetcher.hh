<?hh // strict

class ProductionSessionDataFetcher implements SessionDataFetcher {

  public function __construct(
    private RawSessionDataFetcher $rawSessionDataFetcher,
    private Logger $logger,
    private HRTimestampSerializer $timestampSerializer,
    private SessionKeys $sessionKeys
  ) {}

  public function hasSession(): bool {
    $raw_session = $this->rawSessionDataFetcher->fetch();
    return 
      $raw_session->containsKey($this->sessionKeys->getUserAgentIdKey()) &&
      $raw_session->containsKey($this->sessionKeys->getExpirationTimeKey()) &&
      $raw_session->containsKey($this->sessionKeys->getInitiationTimeKey());
  }

  public function getSession(): SessionData {
    // Check for set session
    if (!$this->hasSession()) {
      throw new SessionException(
        "SessionDataFetcher::getSession() called, but no session exists. Make sure valid session exists first using hasSession()"
      ); 
    }

    // Extract session data
    $raw_session = $this->rawSessionDataFetcher->fetch();

    return new SessionData(
      new UnsignedInt((int)$raw_session[$this->sessionKeys->getUserAgentIdKey()]),
      $this->timestampSerializer->deserialize((string)$raw_session[$this->sessionKeys->getExpirationTimeKey()]),
      $this->timestampSerializer->deserialize((string)$raw_session[$this->sessionKeys->getInitiationTimeKey()])
    );
  }
}
