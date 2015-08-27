<?hh // strict

class IntRequestFieldFactoryBuilder extends RequestFieldFactoryBuilder<int> {

  public function __construct() {
    parent::__construct(new IntRequestFieldTypeConverter());
  }
}
