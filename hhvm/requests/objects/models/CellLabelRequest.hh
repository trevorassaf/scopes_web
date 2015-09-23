<?hh // strict

class CreateCellLabelRequest {
  
  const string REQUEST_OBJECT_NAME = "CreateCellLabelRequest";

  const string CELL_NUMBER_KEY = "cell-num";
  const string LABEL_KEY = "label";

  public function __construct(
    private RequestField<UnsignedInt> $cellNumber,
    private RequestField<string> $label
  ) {}

  public function getCellNumber(): RequestField<UnsignedInt> {
    return $this->cellNumber;
  }

  public function getLabel(): RequestField<string> {
    return $this->label;
  }
}

class CreateCellLabelRequestBuilder {

  private ?RequestField<UnsignedInt> $cellNumber;
  private ?RequestField<string> $label;

  public function setCellNumber(
    RequestField<UnsignedInt> $cell_number
  ): this {
    $this->cellNumber = $cell_number;
    return $this;
  }

  public function setLabel(
    RequestField<string> $label
  ): this {
    $this->label = $label;
    return $this;
  }

  public function build(): CreateCellLabelRequest {
    // Check for missing request keys
    if ($this->cellNumber === null) {
      throw new UnsetRequestFieldException(
        CreateCellLabelRequest::REQUEST_OBJECT_NAME,
        CreateCellLabelRequest::CELL_NUMBER_KEY
      );
    } 
    if ($this->label === null) {
      throw new UnsetRequestFieldException(
        CreateCellLabelRequest::REQUEST_OBJECT_NAME,
        CreateCellLabelRequest::LABEL_KEY
      );
    } 

    // Extrude request object
    return new CreateCellLabelRequest(
      $this->cellNumber,
      $this->label 
    );
  }
}
