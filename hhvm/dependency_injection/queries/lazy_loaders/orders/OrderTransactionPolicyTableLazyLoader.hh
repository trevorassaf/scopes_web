<?hh // strict

class OrderTransactionPolicyTableLazyLoader extends LazyLoader<OrderTransactionPolicyTable> {

  protected function make(): OrderTransactionPolicyTable {
    return new OrderTransactionPolicyTable();
  }
}
