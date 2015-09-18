<?hh // strict

class TimestampRequestFieldFactoryBuilder extends RequestFieldFactoryBuilder<Timestamp> {

  public function __construct(
    private LazyLoader<TimestampSerializer> $timestampSerializer
  ) {
    parent::__construct(
      new TimestampFieldConverter(
        $this->timestampSerializer->load()
      )
    );
  }
}
