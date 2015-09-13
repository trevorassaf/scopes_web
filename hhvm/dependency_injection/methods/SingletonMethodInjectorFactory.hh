<?hh // strict

abstract class SingletonMethodInjectorFactory implements MethodInjectorFactory {

  private static ?MethodInjector $methodInjector;

  public function get(): MethodInjector {
    if (self::$methodInjector === null) {
      self::$methodInjector = $this->make(); 
    }    
    return self::$methodInjector;
  }

  abstract protected function make(): MethodInjector;
}
