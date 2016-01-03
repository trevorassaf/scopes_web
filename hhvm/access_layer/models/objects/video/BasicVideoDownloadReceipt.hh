<?hh // strict

class BasicVideoDownloadReceipt implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $basicVideoId,
    private Timestamp $downloadTime
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getBasicVideoId(): UnsignedInt {
    return $this->basicVideoId;
  }

  public function getDownloadTime(): Timestamp {
    return $this->downloadTime;
  }
}
