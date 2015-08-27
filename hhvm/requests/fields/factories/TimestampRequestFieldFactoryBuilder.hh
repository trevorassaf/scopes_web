<?hh // strict

class TimestampRequestFieldFactoryBuilder extends RequestFieldFactoryBuilder<Timestamp> {

  public function __construct() {
    parent::__construct(new TimestampRequestFieldTypeConverter());
  }
}
