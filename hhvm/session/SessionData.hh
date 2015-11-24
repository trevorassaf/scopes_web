<?hh // strict

class SessionData {

  public function __construct(
    private UnsignedInt $userAgentId,
    private Timestamp $expirationTime,
    private Timestamp $initiationTime
  ) {}

  public function getUserAgentId(): UnsignedInt {
    return $this->userAgentId;
  }

  public function getExpirationTime(): Timestamp {
    return $this->expirationTime;
  }

  public function getInitiationTime(): Timestamp {
    return $this->initiationTime;
  }
}
