<?hh // strict

class CompositeVideoTableLazyLoader extends LazyLoader<CompositeVideoTable> {

  protected function make(): CompositeVideoTable {
    return new CompositeVideoTable();
  }
}
