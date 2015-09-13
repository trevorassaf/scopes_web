<?hh // strict

class RegularTimesTableLazyLoader extends LazyLoader<RegularTimesTable> {

  protected function make(): RegularTimesTable {
    return new RegularTimesTable();
  }
}
