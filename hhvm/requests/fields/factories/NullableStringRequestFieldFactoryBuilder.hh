<?hh // strict

class NullableStringRequestFieldFactoryBuilder extends NullableRequestFieldFactoryBuilder<string> {

  public function __construct() {
    parent::__construct(new StringFieldConverter());
  }
}
