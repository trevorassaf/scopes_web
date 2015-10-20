<?hh // strict

class BasicVideosTableLazyLoader extends LazyLoader<BasicVideosTable> {

  protected function make(): BasicVideosTable {
    return new BasicVideosTable();
  }
}
