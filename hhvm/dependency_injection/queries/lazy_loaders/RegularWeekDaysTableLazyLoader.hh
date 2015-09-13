<?hh // strict

class RegularWeekDaysTableLazyLoader extends LazyLoader<RegularWeekDaysTable> {

  protected function make(): RegularWeekDaysTable {
    return new RegularWeekDaysTable();
  }
}
