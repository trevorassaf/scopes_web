<?hh // strict

class IrregularDatesTableLazyLoader extends LazyLoader<IrregularDatesTable> {

  protected function make(): IrregularDatesTable {
    return new IrregularDatesTable();
  }
}
