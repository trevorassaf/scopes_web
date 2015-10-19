<?hh // strict

class ConfirmedOrderWithCellLabels {

  public function __construct(
    private ConfirmedOrder $confirmedOrder,
    private ImmVector<CellLabel> $cellLabels
  ) {
    invariant(
      $this->confirmedOrder->getScopesCount()->getNumber() 
        === $this->cellLabels->count(),
      "Number of cell labels must be the same!"
    );
  }

  public function getConfirmedOrder(): ConfirmedOrder {
    return $this->confirmedOrder;
  }

  public function getCellLabels(): ImmVector<CellLabel> {
    return $this->cellLabels;
  }
}
