<?hh // strict

abstract class SingletonQueryInjectorFactory implements QueryInjectorFactory {

  private static ?QueryInjector $queryInjector; 

  public function get(): QueryInjector {
    if (self::$queryInjector === null) {
      self::$queryInjector = $this->makeQueryInjector();
    } 
    return self::$queryInjector;
  }

  abstract protected function makeQueryInjector(): QueryInjector;
}
