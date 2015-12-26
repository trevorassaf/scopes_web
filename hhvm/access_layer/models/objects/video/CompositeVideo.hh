<?hh // strict

class CompositeVideo implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $completedCompositeVideoId,
    private Timestamp $expirationTime,
    private Time $duration,
    private UnsignedInt $mimeId
  ) {}
  
  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getCompletedCompositeVideoId(): UnsignedInt {
    return $this->completedCompositeVideoId;
  }

  public function getExpirationTime(): Timestamp {
    return $this->expirationTime;
  }

  public function getDuration(): Time {
    return $this->duration;
  }

  public function getMimeId(): UnsignedInt {
    return $this->mimeId;
  }
}
