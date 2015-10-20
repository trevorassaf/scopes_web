<?hh // strict

class IrregularTimesTableLazyLoader extends LazyLoader<IrregularTimesTable> {

  protected function make(): IrregularTimesTable {
    return new IrregularTimesTable();
  }
}
