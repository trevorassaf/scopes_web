<?hh // strict

class UploadBasicVideosMethod {

  public function __construct(
    private FetchCompletedBasicVideoSetByCompletedOrderQuery $fetchCompletedBasicVideoSetByCompletedOrderQuery,
    private FetchByIdQuery<CompletedOrder> $fetchCompletedOrderByIdQuery,
    private FetchByIdQuery<ConfirmedOrder> $fetchConfirmedOrderByIdQuery,
    private InsertQuery<BasicVideo> $insertBasicVideoQuery,
    private InsertQuery<CompletedBasicVideoSet> $insertCompletedBasicVideoSetQuery,
    private CompletedBasicVideoSetTable $completedBasicVideoSetTable,
    private Logger $logger,
    private TimestampBuilder $timestampBuilder,
    private HRTimestampSerializer $timestampSerializer
  ) {}

  public function upload(UnsignedInt $completed_order_id): void {
    // Log file upload
    $this->logger->info(
      "Uploading basic video set for CompletedOrder (id="
      . $completed_order_id->getNumber() . ")"
    );

    // Fetch completed order
    $fetch_completed_order_handle = $this->fetchCompletedOrderByIdQuery->fetch(
      $completed_order_id
    );

    $completed_order = $fetch_completed_order_handle
      ->getWaitHandle()
      ->join();

    // Check that completed order exists
    if ($completed_order === null) {
      $this->logger->info(
        "CompletedOrder (id=" . $completed_order_id->getNumber() . ") not found!"
      );

      throw new NonextantObjectException(
        "CompletedOrder (id=" . $completed_order_id->getNumber() . ") not found!",
        ObjectType::COMPLETED_ORDER
      );
    }

    // Fetch confirmed order
    $fetch_confirmed_order_handle = $this->fetchConfirmedOrderByIdQuery->fetch(
      $completed_order->getConfirmedOrderId()
    );

    $confirmed_order = $fetch_confirmed_order_handle
      ->getWaitHandle()
      ->join();

    // Check that confirmed order exists
    if ($confirmed_order === null) {
      $this->logger->info(
        "ConfirmedOrder (id=" . $completed_order->getConfirmedOrderId()->getNumber()
        . ") not found!"
      );

      throw new NonextantObjectException(
        "ConfirmedOrder (id=" . $completed_order->getConfirmedOrderId()->getNumber()
        . ") not found!",
        ObjectType::CONFIRMED_ORDER
      );
    }

    // Register basic video set with db
    $upload_time = $this->timestampBuilder->now();

    $insert_basic_video_set_handle = $this->insertCompletedBasicVideoSetQuery->insert(
      ImmMap{
        $this->completedBasicVideoSetTable->getCompletedOrderIdKey() => $completed_order->getId()->getNumber(),
        $this->completedBasicVideoSetTable->getTimeCompletedKey() => $this->timestampSerializer->serialize($upload_time)
      }  
    );

    $basic_video_set = $insert_basic_video_set_handle
      ->getWaitHandle()
      ->join();

    //// Upload videos to file system and place into db
    $files = $this->getFiles();

    // Fail if files not uploaded
    if ($files === null || $files->isEmpty()) {
      $this->logger->info(
        "No video files found!"   
      );

      throw new InvalidFileUploadException();   
    }

    $scopes_count = $confirmed_order->getScopesCount();

    for ($i = 0; $i < $scopes_count->getNumber(); ++$i) {
       
    }
  }

  private function getFiles(): ?ImmMap<string, mixed> {
    // UNSAFE
    return $_FILES;
  }
}
