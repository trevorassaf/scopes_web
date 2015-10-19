<?hh // strict

class CreateCellLabelRequest {

  public function __construct(
    private string $label
  ) {}

  public function getLabel(): string {
    return $this->label;
  }
}
