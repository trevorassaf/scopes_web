<?hh // strict

class ConfirmOrderApiRequestFactory implements RequestFactory<ConfirmOrderApiRequest> {

  private RequestFieldFactory<UnsignedInt> $reserveOrderIdFieldFactory;
  private RequestFieldFactory<string> $titleFieldFactory;
  private RequestFieldFactory<string> $descriptionFieldFactory;
  private RequestFieldFactory<UnsignedInt> $shortCodeIdFieldFactory;
  private EditedVideoOrderApiRequestFactory $editedVideoOrderRequestFactory;

  public function __construct() {
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $string_field_factory_builder = new StringRequestFieldFactoryBuilder();

    // Create reserve order id field factory 
    $this->reserveOrderIdFieldFactory = $uint_field_factory_builder->build();

    // Create title field factory
    $this->titleFieldFactory = $string_field_factory_builder->build();

    // Create description field factory
    $this->descriptionFieldFactory = $string_field_factory_builder->build();

    // Create short coding field factory
    $this->shortCodeIdFieldFactory = $uint_field_factory_builder->build();

    // Create edited-video-order-request-factory
    $this->editedVideoOrderRequestFactory = new EditedVideoOrderApiRequestFactory();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): ConfirmOrderApiRequest {
    $confirmed_order_request_builder = new ConfirmOrderApiRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case ConfirmOrderApiRequest::RSVD_ORDER_ID_KEY:
          $confirmed_order_request_builder->setRsvdOrderId(
            $this->reserveOrderIdFieldFactory->make($key, $value)
          );
          break;
        case ConfirmOrderApiRequest::TITLE_KEY:
          $confirmed_order_request_builder->setTitle(
            $this->titleFieldFactory->make($key, $value)
          );
          break;
        case ConfirmOrderApiRequest::DESCRIPTION_KEY:
          $confirmed_order_request_builder->setDescription(
            $this->descriptionFieldFactory->make($key, $value)
          );
          break;
        case ConfirmOrderApiRequest::SHORT_CODE_KEY:
          $confirmed_order_request_builder->setShortCodeId(
            $this->shortCodeIdFieldFactory->make($key, $value)
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
