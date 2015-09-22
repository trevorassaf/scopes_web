<?hh // strict

class TimestampRequestFieldFactoryBuilder extends RequestFieldFactoryBuilder<Timestamp> {

  public function __construct(
    private TimestampSerializer $timestampSerializer
  ) {
    parent::__construct(
      new TimestampFieldConverter($this->timestampSerializer)
    );
  }
}
