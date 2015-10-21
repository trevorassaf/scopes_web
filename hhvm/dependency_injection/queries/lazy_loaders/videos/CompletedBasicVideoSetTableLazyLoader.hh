<?hh // strict

class CompletedBasicVideoSetTableLazyLoader extends LazyLoader<CompletedBasicVideoSetTable> {

  protected function make(): CompletedBasicVideoSetTable {
    return new CompletedBasicVideoSetTable();
  }
}
