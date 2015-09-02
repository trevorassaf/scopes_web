<?hh // strict

class FloatRequestFieldFactoryBuilder extends RequestFieldFactoryBuilder<float> {

  public function __construct() {
    parent::__construct(new FloatFieldConverter());
  }
}
