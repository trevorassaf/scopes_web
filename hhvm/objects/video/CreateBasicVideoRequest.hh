<?hh // strict

class CreateBasicVideoRequest {

  public function __construct(
    private Timestamp $expirationTime
  ) {}

  public function getExpirationTime(): Timestamp {
    return $this->expirationTime;
  }
}
