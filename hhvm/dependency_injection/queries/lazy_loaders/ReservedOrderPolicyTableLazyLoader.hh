<?hh // strict

class ReservedOrderPolicyTableLazyLoader extends LazyLoader<ReservedOrderPolicyTable> {
 
  protected function make(): ReservedOrderPolicyTable {
    return new ReservedOrderPolicyTable();
  }
}
