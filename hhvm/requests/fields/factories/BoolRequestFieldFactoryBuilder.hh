<?hh // strict

class BoolRequestFieldFactoryBuilder extends RequestFieldFactoryBuilder<bool> {

  public function __construct() {
    parent::__construct(new BoolRequestFieldTypeConverter());
  }
}
