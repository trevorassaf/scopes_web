<?hh // strict

class CreateCellLabelRequest {
  
  const string REQUEST_OBJECT_NAME = "CreateCellLabelRequest";

  const string LABEL_KEY = "label";

  public function __construct(
    private RequestField<string> $label
  ) {}

  public function getLabel(): RequestField<string> {
    return $this->label;
  }
}

class CreateCellLabelRequestBuilder {

  private ?RequestField<string> $label;

  public function setLabel(
    RequestField<string> $label
  ): this {
    $this->label = $label;
    return $this;
  }

  public function build(): CreateCellLabelRequest {
    // Check for missing request keys
    if ($this->label === null) {
      throw new UnsetRequestFieldException(
        CreateCellLabelRequest::REQUEST_OBJECT_NAME,
        CreateCellLabelRequest::LABEL_KEY
      );
    } 

    // Extrude request object
    return new CreateCellLabelRequest(
      $this->label 
    );
  }
}
