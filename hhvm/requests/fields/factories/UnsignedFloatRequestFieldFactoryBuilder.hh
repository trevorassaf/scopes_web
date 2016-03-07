<?hh // strict

class UnsignedFloatRequestFieldFactoryBuilder extends RequestFieldFactoryBuilder<UnsignedFloat> {

  public function __construct() {
    parent::__construct(new UnsignedFloatFieldConverter());
  }
}
