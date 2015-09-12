<?hh // strict

abstract class LazyLoad<T> {

  private ?T $t;

  public function get(): T {
    if ($this->t === null) {
      $this->t = $this->load();
    }
    return $this->t;
  }

  abstract protected function load(): T;
}
