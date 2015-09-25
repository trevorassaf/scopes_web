<?hh // strict

class UpdateCellLabelRequestFactory implements RequestFactory<UpdateCellLabelRequest> {

  private RequestFieldFactory<UnsignedInt> $cellLabelIdFieldFactory;
  private RequestFieldFactory<string> $labelIdFieldFactory;

  public function __construct() {
    // Create cell label id field factory
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $this->cellLabelIdFieldFactory = $uint_field_factory_builder->build();

    // Create label field factory 
    $string_field_factory_builder = new StringRequestFieldFactoryBuilder();
    $this->labelIdFieldFactory = $string_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): UpdateCellLabelRequest {
    $update_cell_label_request_builder = new UpdateCellLabelRequestBuilder(); 
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
      case UpdateCellLabelRequest::CELL_LABEL_ID_KEY:
        $update_cell_label_request_builder->setCellLabelId(
          $this->cellLabelIdFieldFactory->make($key, $value)
        );
        break;
      case UpdateCellLabelRequest::LABEL_KEY:
        $update_cell_label_request_builder->setLabel(
          $this->labelIdFieldFactory->make($key, $value) 
        );
        break;
      default:
        throw new UnexpectedRequestFieldKeyException(__CLASS__, $key);
        break;
      }
    }
    return $update_cell_label_request_builder->build();
  }
}
