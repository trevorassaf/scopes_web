<?hh // strict

class CreateCellLabelRequestFactory implements RequestFactory<CreateCellLabelRequest> {

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

  public function make(ImmMap<string, mixed> $raw_field_map): CreateCellLabelRequest {

ob_start();
var_dump($raw_field_map);
$contents = ob_get_contents();
ob_end_clean();
error_log("CreateCellLabelRequestFactory::make() cell label");
error_log($contents);

    $cell_label_request_builder = new CreateCellLabelRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case CreateCellLabelRequest::LABEL_KEY:
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
