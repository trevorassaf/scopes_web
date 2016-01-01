<?hh // strict

class CompletedBasicVideoSet implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $completedOrderId
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getCompletedOrderId(): UnsignedInt {
    return $this->completedOrderId;
  }
}
