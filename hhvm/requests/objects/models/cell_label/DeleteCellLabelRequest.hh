<?hh // strict

class DeleteCellLabelRequest {

  const string REQUEST_OBJECT_NAME = "UpdateCellLabelRequest";

  const string CELL_LABEL_ID_KEY = "id";

  public function __construct(
    private RequestField<UnsignedInt> $cellLabelId
  ) {}

  public function getCellLabelId(): RequestField<UnsignedInt> {
    return $this->cellLabelId;
  }
}

class DeleteCellLabelRequestBuilder {

  private ?RequestField<UnsignedInt> $cellLabelId;

  public function setCellLabelId(RequestField<UnsignedInt> $id): this {
    $this->cellLabelId = $id; 
    return $this;
  }

  public function build(): DeleteCellLabelRequest {
    if ($this->cellLabelId === null) {
      throw new UnsetRequestFieldException(
        DeleteCellLabelRequest::REQUEST_OBJECT_NAME,
        DeleteCellLabelRequest::CELL_LABEL_ID_KEY 
      );
    }    

    return new DeleteCellLabelRequest($this->cellLabelId);
  }
}
