<?hh // strict

class InvalidCellLabelCountException extends MethodException {

  public function __construct(
    UnsignedInt $expected_cell_labels,
    UnsignedInt $provided_cell_labels
  ) {
    parent::__construct(
      $this->serializeErrorMessage(
        $expected_cell_labels,
        $provided_cell_labels
      )
    );
  }

  private function serializeErrorMessage(
    UnsignedInt $expected_cell_labels,
    UnsignedInt $provided_cell_labels
  ): string {
    return "Expected cell label count: " . $expected_cell_labels->getNumber() .
      ", provided cell label count: " . $provided_cell_labels->getNumber();
  }
}
