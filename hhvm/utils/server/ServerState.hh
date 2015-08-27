<?hh // strict

interface ServerState<T> {

  public function get(): T;
}
