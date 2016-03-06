<?hh // strict

class ConfirmOrderApiRequestFactory implements RequestFactory<ConfirmOrderApiRequest> {

  private RequestFieldFactory<UnsignedInt> $scopesCountFieldFactory;
  private RequestFieldFactory<Timestamp> $startTimestampFieldFactory;
  private RequestFieldFactory<UnsignedInt> $experimentDurationFieldFactory;
  private RequestFieldFactory<UnsignedInt> $shortCodeIdFieldFactory;

  public function __construct(
    private TimestampRequestFieldFactoryBuilder $timestampRequestFieldFactoryBuilder
  ) {
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();

    // Create scopes-count field factory 
    $this->scopesCountFieldFactory = $uint_field_factory_builder->build();
    
    // Create start time field factory
    $this->startTimestampFieldFactory = $this->timestampRequestFieldFactoryBuilder->build();

    // Create experiment duration field factory
    $this->experimentDurationFieldFactory = $uint_field_factory_builder->build();
    
    // Create short coding field factory
    $this->shortCodeIdFieldFactory = $uint_field_factory_builder->build();
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
        case ConfirmOrderApiRequest::START_TIMESTAMP_KEY:
          $confirmed_order_request_builder->setStartTimestamp(
            $this->startTimestampFieldFactory->make($key, $value)
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
        default:
          throw new UnexpectedRequestFieldKeyException(__CLASS__, $key);
          break;
      }
    }
    return $confirmed_order_request_builder->build();
  }
}
