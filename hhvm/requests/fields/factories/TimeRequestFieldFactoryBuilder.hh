<?hh // strict

class TimeRequestFieldFactoryBuilder extends RequestFieldFactoryBuilder<Time> {

  public function __construct(
    private TimeSerializer $timeSerializer
  ) {
    parent::__construct(
      new TimeFieldConverter($this->timeSerializer)
    );
  }
}
