<?hh // strict

class ReservedOrderScopeMapping {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $reservedOrderId,
    private UnsignedInt $virtualScopeIndex,
    private UnsignedInt $physicalScopeIndex
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getReservedOrderId(): UnsignedInt {
    return $this->reservedOrderId;
  }

  public function getVirtualScopeIndex(): UnsignedInt {
    return $this->virtualScopeIndex;
  }

  public function getPhysicalScopeIndex(): UnsignedInt {
    return $this->physicalScopeIndex;
  }
}
