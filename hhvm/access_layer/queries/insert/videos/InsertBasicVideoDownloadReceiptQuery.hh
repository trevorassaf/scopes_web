<?hh // strict

class InsertBasicVideoDownloadReceiptQuery {

  public function __construct(
    private InsertQuery<BasicVideoDownloadReceipt> $insertQuery,
    private BasicVideoDownloadReceiptsTable $table,
    private HRTimestampSerializer $timestampSerializer
  ) {}

  public async function insert(
    UnsignedInt $basic_video_id,
    Timestamp $download_time
  ): Awaitable<BasicVideoDownloadReceipt> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->table->getBasicVideoIdKey() => $basic_video_id->getNumber(),
        $this->table->getDownloadTimeKey() => $this->timestampSerializer->serialize($download_time),
      }
    );
  }
}
