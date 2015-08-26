<?hh // strict

class CellLabelRequest {

  public function __construct(
    private UnsignedInt $confirmedOrderId,
    private UnsignedInt $cellNumber,
    private string $label
  ) {}

  public function getConfirmedOrderId(): UnsignedInt {
    return $this->confirmedOrderId;
  }

  public function getCellNumber(): UnsignedInt {
    return $this->cellNumber;
  }

  public function getLabel(): string {
    return $this->label;
  }
}
