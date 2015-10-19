<?hh // strict

class CellLabel implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $editedVideoOrderId,
    private UnsignedInt $cellNumber,
    private string $label
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getEditedVideoOrderId(): UnsignedInt {
    return $this->editedVideoOrderId;
  }

  public function getCellNumber(): UnsignedInt {
    return $this->cellNumber;
  }

  public function getLabel(): string {
    return $this->label;
  }
}
