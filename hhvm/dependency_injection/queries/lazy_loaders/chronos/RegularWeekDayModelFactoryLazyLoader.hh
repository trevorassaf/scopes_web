<?hh // strict

class RegularWeekDayModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<RegularWeekDay>> {

  protected function make(): ConcreteModelFactory<RegularWeekDay> {
    return new RegularWeekDayFactory(); 
  }
}
