<?hh // strict

class ConfirmedOrderScopeMapping {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $confirmedOrderId,
    private UnsignedInt $virtualScopeIndex,
    private UnsignedInt $physicalScopeIndex
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getConfirmedOrderId(): UnsignedInt {
    return $this->confirmedOrderId;
  }

  public function getVirtualScopeIndex(): UnsignedInt {
    return $this->virtualScopeIndex;
  }

  public function getPhysicalScopeIndex(): UnsignedInt {
    return $this->physicalScopeIndex;
  }
}
