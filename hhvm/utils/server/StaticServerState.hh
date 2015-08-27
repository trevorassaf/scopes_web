<?hh // strict

class StaticServerState<T> implements ServerState<T> {
  
  public function __construct(
    private T $t
  ) {}

  public function get(): T {
    return $this->t; 
  }
}
