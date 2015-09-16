<?hh // strict

class CellLabelsTableLazyLoader extends LazyLoader<CellLabelsTable> {
  
  protected function make(): CellLabelsTable {
    return new CellLabelsTable();
  }
}
