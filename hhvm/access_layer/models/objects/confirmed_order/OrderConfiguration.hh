<?hh

class OrderConfiguration {

  public function __construct(
    private UnsignedInt $scopesCount,
    private UnsignedInt $maxExperimentDuration,
    private Timestamp $timeEnacted
  ) {}

  public function getScopesCount(): UnsignedInt {
    return $this->scopesCount;
  }

  public function getMaxExperimentDuration(): UnsignedInt {
    return $this->maxExperimentDuration;
  }

  public function getTimeEnacted(): Timestamp {
    return $this->timeEnacted;
  }
}
