<?hh // strict

class MarkBasicVideoDownloadedMethod {

  public function __construct(
    private InsertBasicVideoDownloadReceiptQuery $insertBasicVideoDownloadReceiptQuery,
    private TimestampBuilder $timestampBuilder
  ) {}

  public function mark(
    UnsignedInt $basic_video_id
  ): BasicVideoDownloadReceipt {
    try {
      // Get download timestamp 
      $download_time = $this->timestampBuilder->now();

      // Insert download-receipt record
      $insert_handle = $this->insertBasicVideoDownloadReceiptQuery->insert(
        $basic_video_id,
        $download_time
      );

      return $insert_handle
        ->getWaitHandle()
        ->join();

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
