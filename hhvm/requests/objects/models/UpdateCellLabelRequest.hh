<?hh // strict

class UpdateCellLabelRequest {

  const string REQUEST_OBJECT_NAME = "UpdateCellLabelRequest";

  const string CELL_LABEL_ID_KEY = "id";
  const string LABEL_KEY = "label";

  public function __construct(
    private RequestField<UnsignedInt> $cellLabelId,
    private RequestField<string> $label
  ) {}

  public function getCellLabelId(): RequestField<UnsignedInt> {
    return $this->cellLabelId;
  }

  public function getLabel(): RequestField<string> {
    return $this->label;
  }
}

class UpdateCellLabelRequestBuilder {

  private ?RequestField<UnsignedInt> $cellLabelId;
  private ?RequestField<string> $label;

  public function setCellLabelId(RequestField<UnsignedInt> $id): this {
    $this->cellLabelId = $id; 
    return $this;
  }

  public function setLabel(RequestField<string> $label): this {
    $this->label = $label;
    return $this;
  }

  private function checkNotNull<T>(string $key, ?T $value): T {
    if ($value === null) {
      throw new UnsetRequestFieldException(
        UpdateCellLabelRequest::REQUEST_OBJECT_NAME,
        $key
      );
    } 
    return $value;
  }

  public function build(): UpdateCellLabelRequest {
    return new UpdateCellLabelRequest(
      $this->checkNotNull(
        UpdateCellLabelRequest::CELL_LABEL_ID_KEY,
        $this->cellLabelId
      ),
      $this->checkNotNull(
        UpdateCellLabelRequest::LABEL_KEY,
        $this->label
      )
    ); 
  }
}
