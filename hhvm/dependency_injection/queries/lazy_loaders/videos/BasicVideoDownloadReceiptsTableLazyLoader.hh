<?hh // strict

class BasicVideoDownloadReceiptsTableLazyLoader extends LazyLoader<BasicVideoDownloadReceiptsTable> {

  protected function make(): BasicVideoDownloadReceiptsTable {
    return new BasicVideoDownloadReceiptsTable();
  }
}
