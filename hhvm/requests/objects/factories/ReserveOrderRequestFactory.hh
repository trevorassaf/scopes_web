<?hh // strict

class ReserveOrderRequestFactory implements RequestFactory<ReserveOrderRequest> {

  private RequestFieldFactory<UnsignedInt> $userIdFieldFactory;
  private RequestFieldFactory<UnsignedInt> $scopesCountFieldFactory;
  private RequestFieldFactory<Timestamp> $startTimeFieldFactory;
  private RequestFieldFactory<Timestamp> $endTimeFieldFactory;

  public function __construct(
    private TimestampRequestFieldFactoryBuilder $timestampRequestFieldFactoryBuilder
  ) {
    // Create user id field factory
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $this->userIdFieldFactory = $uint_field_factory_builder->build();

    // Create scopes count field factory
    $this->scopesCountFieldFactory = $uint_field_factory_builder->build();

    // Create start time field factory
    $this->startTimeFieldFactory = $this->timestampRequestFieldFactoryBuilder->build();

    // Create end time field factory
    $this->endTimeFieldFactory = $this->timestampRequestFieldFactoryBuilder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): ReserveOrderRequest {
    $reserve_order_request_builder = new ReserveOrderRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case ReserveOrderRequest::USER_ID_KEY:
          $reserve_order_request_builder->setUserId(
            $this->userIdFieldFactory->make($key, $value)
          );
          break;
        case ReserveOrderRequest::SCOPES_COUNT_KEY:
          $reserve_order_request_builder->setScopesCount(
            $this->scopesCountFieldFactory->make($key, $value)
          );
          break;
        case ReserveOrderRequest::START_TIME_KEY:
          $reserve_order_request_builder->setStartTime(
            $this->startTimeFieldFactory->make($key, $value)
          );
          break;
        case ReserveOrderRequest::END_TIME_KEY:
          $reserve_order_request_builder->setEndTime(
            $this->endTimeFieldFactory->make($key, $value)
          );
          break;
        default:
          throw new UnexpectedRequestFieldKeyException(__CLASS__, $key);
          break;
      }
    }
    return $reserve_order_request_builder->build();
  }
}
