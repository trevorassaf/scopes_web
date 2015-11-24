<?hh // strict

class RawSessionDataWriter {

  public function __construct(
    private SessionDataFetcher $sessionDataFetcher,
    private Logger $logger,
    private HRTimestampSerializer $timestampSerializer,
    private SessionKeys $sessionKeys
  ) {}

  public function initialize(
    UnsignedInt $user_agent_id,
    Timestamp $expiration_time,
    Timestamp $initiation_time
  ): SessionData {
    // Check if session already exists
    if ($this->sessionDataFetcher->hasSession()) {
      $this->logger->error(
        "Can't initialize session b/c session already exists!"
      ); 
      throw new Exception();
    }

    // Write session values
    $this->writeUserAgentId($user_agent_id);
    $this->writeExpirationTime($expiration_time);
    $this->writeInitiationTime($initiation_time);

    return new SessionData(
      $user_agent_id,
      $expiration_time,
      $initiation_time
    );
  }

  public function setExpirationTime(
    Timestamp $expiration_time
  ): SessionData {
    // Check if session already exists
    if (!$this->sessionDataFetcher->hasSession()) {
      $this->logger->error(
        "Can't set expiration-time when session doesn't exist!"
      ); 
      throw new Exception();
    }

    // Write expiration-time data
    $this->writeExpirationTime($expiration_time); 

    return $this->sessionDataFetcher->getSession();
  }

  public function close(): void {
    // Check if session already exists
    if (!$this->sessionDataFetcher->hasSession()) {
      $this->logger->error(
        "Can't destroy session when session doesn't exist!"
      ); 
      throw new Exception();
    }

    $this->deleteSessionValues();

    // UNSAFE
    session_destroy();
  }

  private function deleteSessionValues(): void {
    // UNSAFE
    unset($_SESSION[$this->sessionKeys->getUserAgentIdKey()]);
    unset($_SESSION[$this->sessionKeys->getExpirationTimeKey()]);
    unset($_SESSION[$this->sessionKeys->getInitiationTimeKey()]);
  }

  private function writeUserAgentId(UnsignedInt $user_agent_id): void {
    // UNSAFE
    $_SESSION[$this->sessionKeys->getUserAgentIdKey()] = $user_agent_id->getNumber();
  }

  private function writeExpirationTime(Timestamp $expiration_time): void {
    // UNSAFE
    $_SESSION[$this->sessionKeys->getExpirationTimeKey()] =
        $this->timestampSerializer->deserialize($expiration_time);
  }
  
  private function writeInitiationTime(Timestamp $initiation_time): void {
    // UNSAFE
    $_SESSION[$this->sessionKeys->getInitiationTimeKey()] =
        $this->timestampSerializer->deserialize($initiation_time);
  }

}
