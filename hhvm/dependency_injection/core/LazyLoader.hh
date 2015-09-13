<?hh // strict

abstract class LazyLoader<T> {

  private ?T $t;

  public function load(): T {
    if ($this->t === null) {
      $this->t = $this->load();
    }
    return $this->t;
  }

  abstract protected function make(): T;
}
