<?hh // strict

class CompletedCompositeVideoTableLazyLoader extends LazyLoader<CompletedCompositeVideoTable> {

  protected function make(): CompletedCompositeVideoTable {
    return new CompletedCompositeVideoTable();
  }
}
