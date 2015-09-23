<?hh // strict

class ConfirmOrderRequestFactory implements RequestFactory<ConfirmOrderRequest> {

  private RequestFieldFactory<UnsignedInt> $reserveOrderIdFieldFactory;
  private RequestFieldFactory<string> $titleFieldFactory;
  private RequestFieldFactory<string> $descriptionFieldFactory;
  private RequestFieldFactory<string> $shortCodeFieldFactory;
  private RequestFieldFactory<UnsignedInt> $recordingDurationFieldFactory;
  private ObjectVectorRequestFieldFactory<CreateCellLabelRequest> $cellLabelsRequestFieldFactory;

  public function __construct() {
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $string_field_factory_builder = new StringRequestFieldFactoryBuilder();

    // Create reserve order id field factory 
    $this->reserveOrderIdFieldFactory = $uint_field_factory_builder->build();

    // Create recording duration field factory
    $this->recordingDurationFieldFactory = $uint_field_factory_builder->build();

    // Create title field factory
    $this->titleFieldFactory = $string_field_factory_builder->build();

    // Create description field factory
    $this->descriptionFieldFactory = $string_field_factory_builder->build();

    // Create short coding field factory
    $this->shortCodeFieldFactory = $string_field_factory_builder->build();

    // Create cell label request
    $cell_label_vector_factory_builder = new CreateCellLabelVectorRequestFieldFactoryBuilder();
    $this->cellLabelsRequestFieldFactory = $cell_label_vector_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): ConfirmOrderRequest {

ob_start();
var_dump($raw_field_map);
$contents = ob_get_contents();
ob_end_clean();
error_log("ConfirmOrderRequestFactory::make() raw field map");
error_log($contents);

    $confirmed_order_request_builder = new ConfirmOrderRequestBuilder();

    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case ConfirmOrderRequest::RSVD_ORDER_ID_KEY:
          $confirmed_order_request_builder->setRsvdOrderId(
            $this->reserveOrderIdFieldFactory->make($key, $value)
          );
          break;
        case ConfirmOrderRequest::TITLE_KEY:
          $confirmed_order_request_builder->setTitle(
            $this->titleFieldFactory->make($key, $value)
          );
          break;
        case ConfirmOrderRequest::DESCRIPTION_KEY:
          $confirmed_order_request_builder->setDescription(
            $this->descriptionFieldFactory->make($key, $value)
          );
          break;
        case ConfirmOrderRequest::SHORT_CODE_KEY:
          $confirmed_order_request_builder->setShortCode(
            $this->shortCodeFieldFactory->make($key, $value)
          );
          break;
        case ConfirmOrderRequest::RECORDING_DURATION_KEY:
          $confirmed_order_request_builder->setRecordingDuration(
            $this->recordingDurationFieldFactory->make($key, $value)
          );
          break;
        case ConfirmOrderRequest::CELL_LABEL_REQUESTS_KEY:
          $confirmed_order_request_builder->setCellLabels(
            $this->cellLabelsRequestFieldFactory->make($key, $value)
          );
          break;
        default:
          throw new UnexpectedRequestFieldKeyException(__CLASS__, $key);
          break;
      }
    }
    return $confirmed_order_request_builder->build();
  }
}
