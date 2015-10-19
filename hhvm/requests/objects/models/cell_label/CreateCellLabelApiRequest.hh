<?hh // strict

class CreateCellLabelApiRequest {
  
  const string REQUEST_OBJECT_NAME = "CreateCellLabelApiRequest";

  const string LABEL_KEY = "label";

  public function __construct(
    private RequestField<string> $label
  ) {}

  public function getLabel(): RequestField<string> {
    return $this->label;
  }
}

class CreateCellLabelApiRequestBuilder {

  private ?RequestField<string> $label;

  public function setLabel(
    RequestField<string> $label
  ): this {
    $this->label = $label;
    return $this;
  }

  public function build(): CreateCellLabelApiRequest {
    // Check for missing request keys
    if ($this->label === null) {
      throw new UnsetRequestFieldException(
        CreateCellLabelApiRequest::REQUEST_OBJECT_NAME,
        CreateCellLabelApiRequest::LABEL_KEY
      );
    } 

    // Extrude request object
    return new CreateCellLabelApiRequest(
      $this->label 
    );
  }
}
