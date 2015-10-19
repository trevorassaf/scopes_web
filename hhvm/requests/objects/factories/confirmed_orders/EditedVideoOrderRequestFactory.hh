<?hh // strict

class EditedVideoOrderApiRequestFactory implements RequestFactory<EditedVideoOrderApiRequest> {

  private RequestFieldFactory<UnsignedInt> $recordingDurationFieldFactory;
  private ObjectVectorApiRequestFieldFactory<CreateCellLabelApiRequest> $cellLabelsRequestFieldFactory;

  public function __construct() {
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
     
    // Create recording duration field factory
    $this->recordingDurationFieldFactory = $uint_field_factory_builder->build();

    // Create cell label request
    $cell_label_vector_factory_builder = new CreateCellLabelVectorApiRequestFieldFactoryBuilder();
    $this->cellLabelsRequestFieldFactory = $cell_label_vector_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): EditedVideoOrderApiRequest {
    $edited_order_request_builder = new EditedVideoOrderApiRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case EditedVideoOrderApiRequest::RECORDING_DURATION_KEY:
          $edited_order_request_builder->setRecordingDurationMinutes(
            $this->recordingDurationFieldFactory->make($key, $value)
          );
          break; 
        case EditedVideoOrderApiRequest::CELL_LABEL_KEY:
          $edited_order_request_builder->setCellLabels(
            $this->cellLabelsRequestFieldFactory->make($key, $value)
          );
          break; 
        default:
          throw new UnexpectedRequestFieldKeyException(__CLASS__, $key);
          break;
      } 
    }
    return $edited_order_request_builder->build();
  }
}
