<?hh // strict

class NullableUnsignedIntRequestFieldFactoryBuilder extends NullableRequestFieldFactoryBuilder<UnsignedInt> {

  public function __construct() {
    parent::__construct(new UnsignedIntFieldConverter());
  }
}
