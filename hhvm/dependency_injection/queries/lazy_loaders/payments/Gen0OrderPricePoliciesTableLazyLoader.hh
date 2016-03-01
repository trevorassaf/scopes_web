<?hh // strict

class Gen0OrderPricePoliciesTableLazyLoader extends LazyLoader<Gen0OrderPricePoliciesTable> {

  protected function make(): Gen0OrderPricePoliciesTable {
    return new Gen0OrderPricePoliciesTable();
  }
}
