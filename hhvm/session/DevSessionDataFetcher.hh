<?hh // strict

class DevSessionDataFetcher implements SessionDataFetcher {

  const int DEV_USER_ID = 1;

  public function __construct(
    private TimestampBuilder $timestampBuilder
  ) {}

  public function hasSession(): bool {
    return true;
  }

  public function getSession(): SessionData {
    $current_time = $this->timestampBuilder->now();
    return new SessionData(
      new UnsignedInt(self::DEV_USER_ID),
      $current_time,
      $current_time
    );
  }
}
