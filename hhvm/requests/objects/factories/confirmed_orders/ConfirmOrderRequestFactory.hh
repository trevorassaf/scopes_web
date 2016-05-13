<?hh // strict

class ConfirmOrderApiRequestFactory implements RequestFactory<ConfirmOrderApiRequest> {

  private RequestFieldFactory<UnsignedInt> $scopesCountFieldFactory;
  private RequestFieldFactory<UnsignedInt> $experimentDurationFieldFactory;
  private RequestFieldFactory<UnsignedInt> $shortCodeIdFieldFactory;
  private RequestFieldFactory<UnsignedFloat> $priceFieldFactory;
  private UnserializedTimestampApiRequestFactory $startTimeFieldFactory;
  private MapApiRequestFieldFactory<string, mixed> $mapFieldFactory;

  public function __construct() {
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();

    // Create scopes-count field factory 
    $this->scopesCountFieldFactory = $uint_field_factory_builder->build();
    
    // Create experiment duration field factory
    $this->experimentDurationFieldFactory = $uint_field_factory_builder->build();
    
    // Create short coding field factory
    $this->shortCodeIdFieldFactory = $uint_field_factory_builder->build();

    // Create price field factory
    $ufloat_field_factory_builder = new UnsignedFloatRequestFieldFactoryBuilder();  
    $this->priceFieldFactory = $ufloat_field_factory_builder->build();

    // Create unserialized timestamp field factory
    $this->startTimeFieldFactory = new UnserializedTimestampApiRequestFactory(); 

    $string_field_factory_builder = new StringRequestFieldFactoryBuilder();
    $mixed_field_factory_builder = new MixedRequestFieldFactoryBuilder();
    $this->mapFieldFactory = new MapApiRequestFieldFactory(
      $string_field_factory_builder->build(),
      $mixed_field_factory_builder->build()
    );
  }

  public function make(ImmMap<string, mixed> $raw_field_map): ConfirmOrderApiRequest {
    $confirmed_order_request_builder = new ConfirmOrderApiRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case ConfirmOrderApiRequest::SCOPES_COUNT_KEY:
          $confirmed_order_request_builder->setScopesCount(
            $this->scopesCountFieldFactory->make($key, $value)
          );
          break;
        case ConfirmOrderApiRequest::START_TIME_KEY:
          $map = $this->mapFieldFactory->convert($key, $value);
          $confirmed_order_request_builder->setStartTime(
            $this->startTimeFieldFactory->make($map->get())
          );
          break;
        case ConfirmOrderApiRequest::DURATION_KEY:
          $confirmed_order_request_builder->setExperimentDuration(
            $this->experimentDurationFieldFactory->make($key, $value)
          );
          break;
        case ConfirmOrderApiRequest::SHORT_CODE_KEY:
          $confirmed_order_request_builder->setShortCodeId(
            $this->shortCodeIdFieldFactory->make($key, $value)
          );
          break;
        case ConfirmOrderApiRequest::PRICE_KEY:
          $confirmed_order_request_builder->setPrice(
            $this->priceFieldFactory->make($key, $value)
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
