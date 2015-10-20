<?hh // strict

class ConfirmedOrderTransactionTableLazyLoader extends LazyLoader<ConfirmedOrderTransactionTable> {

  protected function make(): ConfirmedOrderTransactionTable {
    return new ConfirmedOrderTransactionTable();
  }
}
