<?hh // strict

class UnsignedIntRequestFieldFactoryBuilder extends RequestFieldFactoryBuilder<UnsignedInt> {

  public function __construct() {
    parent::__construct(new UnsignedIntRequestFieldTypeConverter());
  }
}
