<?hh // strict

class RegularWeekDayRegularTimeEdgesTableLazyLoader extends LazyLoader<RegularWeekDayRegularTimeEdgesTable> {

  protected function make(): RegularWeekDayRegularTimeEdgesTable {
    return new RegularWeekDayRegularTimeEdgesTable();
  }
}
