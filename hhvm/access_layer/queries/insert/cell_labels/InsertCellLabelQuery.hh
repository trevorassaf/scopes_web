<?hh // strict

class InsertCellLabelQuery {

  public function __construct(
    private InsertQuery<CellLabel> $insertQuery,
    private CellLabelsTable $cellLabelsTable
  ) {}

  public async function insert(
    UnsignedInt $edited_video_order_id,
    UnsignedInt $cell_number,
    string $label  
  ): Awaitable<CellLabel> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->cellLabelsTable->getEditedVideoOrderIdKey() => $edited_video_order_id->getNumber(),
        $this->cellLabelsTable->getCellNumberKey() => $cell_number->getNumber(),
        $this->cellLabelsTable->getLabelKey() => $label,
      }
    ); 
  }
}
