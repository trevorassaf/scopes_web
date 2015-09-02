<?hh // strict

class ServerState<T> {

  public function __construct(private T $t) {}

  public function get(): T;
}
