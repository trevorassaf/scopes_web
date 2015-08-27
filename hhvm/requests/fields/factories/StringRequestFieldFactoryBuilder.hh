<?hh // strict

class StringRequestFieldFactoryBuilder extends RequestFieldFactoryBuilder<string> {

  public function __construct() {
    parent::__construct(new StringRequestFieldTypeConverter());
  }
}
