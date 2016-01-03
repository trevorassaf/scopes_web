<?hh // strict

class IsBasicVideoDownloadedMethod {

  public function __construct(
    private FetchDownloadReceiptsForBasicVideoQuery $fetchDownloadReceiptsQuery
  ) {}

  public function get(UnsignedInt $video_id): bool {
    try {
      // Fetch download receipts linked with this BasicVideo
      $fetch_download_receipt_handle = $this->fetchDownloadReceiptsQuery->fetch(
        $video_id
      ); 

      $download_receipts = $fetch_download_receipt_handle
        ->getWaitHandle()
        ->join();

      return !$download_receipts->isEmpty();

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
