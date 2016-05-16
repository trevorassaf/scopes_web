<?hh // strict

class PaymentStatusTableLazyLoader extends LazyLoader<PaymentStatusTable> {

  protected function make(): PaymentStatusTable {
    return new PaymentStatusTable();
  }
}
