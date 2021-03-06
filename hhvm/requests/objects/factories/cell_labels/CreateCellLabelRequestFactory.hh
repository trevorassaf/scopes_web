<?hh // strict

class CreateCellLabelApiRequestFactory implements RequestFactory<CreateCellLabelApiRequest> {

  private RequestFieldFactory<UnsignedInt> $cellNumberFieldFactory;
  private RequestFieldFactory<string> $labelFieldFactory;

  public function __construct() {
    // Create cell number field factory
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $this->cellNumberFieldFactory = $uint_field_factory_builder->build();

    // Create label field factory
    $string_field_factory_builder = new StringRequestFieldFactoryBuilder();
    $this->labelFieldFactory = $string_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): CreateCellLabelApiRequest {
    $cell_label_request_builder = new CreateCellLabelApiRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case CreateCellLabelApiRequest::LABEL_KEY:
          $cell_label_request_builder->setLabel(
            $this->labelFieldFactory->make($key, $value)
          );
          break;
        default:
          throw new UnexpectedRequestFieldKeyException(__CLASS__, $key);
          break;
      }
    }
    return $cell_label_request_builder->build();
  }
}
