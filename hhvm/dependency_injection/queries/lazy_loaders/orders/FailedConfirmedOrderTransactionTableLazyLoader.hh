<?hh // strict

class FailedConfirmedOrderTransactionTableLazyLoader extends LazyLoader<FailedConfirmedOrderTransactionTable> {

  protected function make(): FailedConfirmedOrderTransactionTable {
    return new FailedConfirmedOrderTransactionTable();
  }
}
