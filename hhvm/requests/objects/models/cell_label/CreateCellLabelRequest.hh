<?hh // strict

class CellLabelRequest {
  
  const string REQUEST_OBJECT_NAME = "CellLabelRequest";

  const string CONFIRMED_ORDER_ID_KEY = "co-id";
  const string CELL_NUMBER_KEY = "cell-num";
  const string LABEL_KEY = "label";

  public function __construct(
    private RequestField<UnsignedInt> $confirmedOrderId,
    private RequestField<UnsignedInt> $cellNumber,
    private RequestField<string> $label
  ) {}

  public function getConfirmedOrderId(): RequestField<UnsignedInt> {
    return $this->confirmedOrderId;
  }

  public function getCellNumber(): RequestField<UnsignedInt> {
    return $this->cellNumber;
  }

  public function getLabel(): RequestField<string> {
    return $this->label;
  }
}

class CellLabelRequestBuilder {

  private ?RequestField<UnsignedInt> $confirmedOrderId;
  private ?RequestField<UnsignedInt> $cellNumber;
  private ?RequestField<string> $label;

  public function setConfirmedOrderId(
    RequestField<UnsignedInt> $confirmed_order_id
  ): this {
    $this->confirmedOrderId = $confirmed_order_id;
    return $this;
  }

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

  public function build(): CellLabelRequest {
    // Check for missing request keys
    if ($this->confirmedOrderId === null) {
      throw new UnsetRequestFieldException(
        CellLabelRequest::REQUEST_OBJECT_NAME,
        CellLabelRequest::CONFIRMED_ORDER_ID_KEY
      );
    } 
    if ($this->cellNumber === null) {
      throw new UnsetRequestFieldException(
        CellLabelRequest::REQUEST_OBJECT_NAME,
        CellLabelRequest::CELL_NUMBER_KEY
      );
    } 
    if ($this->label === null) {
      throw new UnsetRequestFieldException(
        CellLabelRequest::REQUEST_OBJECT_NAME,
        CellLabelRequest::LABEL_KEY
      );
    } 

    // Extrude request object
    return new CellLabelRequest(
      $this->confirmedOrderId,
      $this->cellNumber,
      $this->label 
    );
  }
}
