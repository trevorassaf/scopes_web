<?hh // strict

class MixedRequestFieldFactoryBuilder extends RequestFieldFactoryBuilder<mixed> {

  public function __construct() {
    parent::__construct(new MixedFieldConverter());
  }
}
