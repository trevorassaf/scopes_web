<?hh // strict

class UpdateConfirmedOrderRequestFactory implements RequestFactory<UpdateConfirmedOrderRequest> {

  private RequestFieldFactory<UnsignedInt> $confirmedOrderIdFieldFactory;
  private RequestFieldFactory<string> $titleFieldFactory;
  private RequestFieldFactory<string> $descriptionFieldFactory;
  private RequestFieldFactory<string> $shortCodeFieldFactory;
  private RequestFieldFactory<UnsignedInt> $recordingDurationFieldFactory;

  public function __construct() {
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $string_field_factory_builder = new StringRequestFieldFactoryBuilder();

    // Create confirmed order id field factory 
    $this->confirmedOrderIdFieldFactory = $uint_field_factory_builder->build();

    // Create recording duration field factory
    $this->recordingDurationFieldFactory = $uint_field_factory_builder->build();

    // Create title duration field factory
    $this->titleFieldFactory = $string_field_factory_builder->build();

    // Create description field factory
    $this->descriptionFieldFactory = $string_field_factory_builder->build();
       
    // Create short code field factory
    $this->shortCodeFieldFactory = $string_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): UpdateConfirmedOrderRequest {
    $update_confirmed_order_request_builder = new UpdateConfirmedOrderRequestBuilder();
  
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case UpdateConfirmedOrderRequest::CONFIRMED_ORDER_ID_KEY:
          $update_confirmed_order_request_builder->setConfirmedOrderId(
            $this->confirmedOrderIdFieldFactory->make($key, $value)
          );
          break;
        case UpdateConfirmedOrderRequest::TITLE_KEY:
          $update_confirmed_order_request_builder->setTitle(
            $this->titleFieldFactory->make($key, $value)
          );
          break;
        case UpdateConfirmedOrderRequest::DESCRIPTION_KEY:
          $update_confirmed_order_request_builder->setDescription(
            $this->descriptionFieldFactory->make($key, $value)
          );
          break;
        case UpdateConfirmedOrderRequest::SHORT_CODE_KEY:
          $update_confirmed_order_request_builder->setShortCode(
            $this->shortCodeFieldFactory->make($key, $value)
          );
          break;
        default:
          throw new UnexpectedRequestFieldKeyException(__CLASS__, $key);
          break;
      } 
    }
    return $update_confirmed_order_request_builder->build(); 
  }
}
