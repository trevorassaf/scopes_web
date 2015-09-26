<?hh // strict

class CellLabelRequestFactory implements RequestFactory<CellLabelRequest> {

  private RequestFieldFactory<UnsignedInt> $confirmedOrderIdFieldFactory;
  private RequestFieldFactory<UnsignedInt> $cellNumberFieldFactory;
  private RequestFieldFactory<string> $labelFieldFactory;

  public function __construct() {
    // Create confirmed order id field factory 
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $this->confirmedOrderIdFieldFactory = $uint_field_factory_builder->build();

    // Create cell number field factory
    $this->cellNumberFieldFactory = $uint_field_factory_builder->build();

    // Create label field factory
    $string_field_factory_builder = new StringRequestFieldFactoryBuilder();
    $this->labelFieldFactory = $string_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): CellLabelRequest {
    $cell_label_request_builder = new CellLabelRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case CellLabelRequest::CONFIRMED_ORDER_ID_KEY:
          $cell_label_request_builder->setConfirmedOrderId(
            $this->confirmedOrderIdFieldFactory->make($key, $value)
          );
          break;
        case CellLabelRequest::CELL_NUMBER_KEY:
          $cell_label_request_builder->setCellNumber(
            $this->cellNumberFieldFactory->make($key, $value)
          );
          break;
        case CellLabelRequest::LABEL_KEY:
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
