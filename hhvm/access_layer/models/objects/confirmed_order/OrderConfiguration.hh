<?hh

class OrderConfiguration {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $scopesCount,
    private UnsignedInt $maxExperimentDuration,
    private Time $startTime,
    private Time $endTime,
    private UnsignedInt $startTimeInterval,
    private UnsignedInt $minDaysInAdvance,
    private UnsignedInt $maxMonthsInAdvance,
    private Timestamp $timeEnacted
  ) {}
  
  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getScopesCount(): UnsignedInt {
    return $this->scopesCount;
  }

  public function getMaxExperimentDuration(): UnsignedInt {
    return $this->maxExperimentDuration;
  }

  public function getStartTime(): Time {
    return $this->startTime;
  }

  public function getEndTime(): Time {
    return $this->endTime;
  }

  public function getStartTimeInterval(): UnsignedInt {
    return $this->startTimeInterval;
  }

  public function getMinDaysInAdvance(): UnsignedInt {
    return $this->minDaysInAdvance;
  }

  public function getMaxMonthsInAdvance(): UnsignedInt {
    return $this->maxMonthsInAdvance;
  }

  public function getTimeEnacted(): Timestamp {
    return $this->timeEnacted;
  }
}
