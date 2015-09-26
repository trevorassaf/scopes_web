<?hh // strict

class DeleteCellLabelRequestFactory {

  private RequestFieldFactory<UnsignedInt> $cellLabelIdFieldFactory;

  public function __construct() {
    // Create call label id field factory
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $this->cellLabelIdFieldFactory = $uint_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): DeleteCellLabelRequest {
    $delete_cell_label_request_builder = new DeleteCellLabelRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case DeleteCellLabelRequest::CELL_LABEL_ID_KEY:
          $delete_cell_label_request_builder->setCellLabelId(
            $this->cellLabelIdFieldFactory->make($key, $value)
          );
          break;
        default:
          throw new UnexpectedRequestFieldKeyException(__CLASS__, $key);
          break;
      }
    }
    return $delete_cell_label_request_builder->build();
  }
}
