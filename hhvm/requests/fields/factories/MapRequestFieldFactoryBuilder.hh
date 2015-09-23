<?hh // strict

class MapRequestFieldFactoryBuilder extends RequestFieldFactoryBuilder<ImmMap<string, mixed>> {

  public function __construct() {
    parent::__construct(new MapRequestFieldFactory());
  }
}
