<?hh // strict

class ShortCodesTableLazyLoader extends LazyLoader<ShortCodeTable> {
  
  protected function make(): ShortCodeTable {
    return new ShortCodeTable();
  }
}
