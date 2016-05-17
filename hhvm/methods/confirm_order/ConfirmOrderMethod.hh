<?hh // strict

class ConfirmOrderMethod {

  public function __construct(
    private FetchIsUserOwnedShortCodeQuery $fetchIsUserOwnedShortCodeQuery,
    private InsertConfirmedOrderQuery $confirmedOrderInsertQuery,
    private ApplyGen0OrderPricePolicyMethod $applyGen0OrderPricePolicyMethod,
    private IsConflictingConfirmedOrderMethod $isConflictingConfirmedOrderMethod,
    private TimestampSegmentFactory $timestampSegmentFactory,
    private TimestampBuilder $timestampBuilder,
    private TimestampOperator $timestampOperator
  ) {}

  public function confirm(
    UnsignedInt $user_id,
    UnsignedInt $scopes_count,
    UnsignedInt $experiment_duration,
    UnsignedInt $short_code_id,
    Timestamp $start_timestamp,
  ): ConfirmedOrder {
    
    // Fail if short code does not belong to this user
    $fetch_is_user_owned_short_code_handle = $this->fetchIsUserOwnedShortCodeQuery->fetch(
      $user_id,
      $short_code_id
    );

    $is_user_owned_short_code = $fetch_is_user_owned_short_code_handle
      ->getWaitHandle()
      ->join();

    if (!$is_user_owned_short_code) {
      throw new UnownedShortCodeException(
        $user_id,
        $short_code_id
      );
    }

    // Compute experiment end-timestamp
    $end_timestamp = $this->timestampOperator->addHours(
      $start_timestamp,
      $experiment_duration
    );

    // Fail if experiment falls beyond permitted timeslots
    $experiment_timestamp_segment = $this->timestampSegmentFactory->make(
      $start_timestamp,
      $end_timestamp
    );

    if (!$this->isConflictingConfirmedOrderMethod->check($experiment_timestamp_segment)) {
      throw new ConflictingConfirmedOrderRequestException();
    }

    // Apply pricing policy
    $current_timestamp = $this->timestampBuilder->now();
    
    $server_price = $this->applyGen0OrderPricePolicyMethod->apply(
      $scopes_count,
      $experiment_duration,
      $current_timestamp
    );

    // Initialize order/payment statuses
    $pending_order_status_type = OrderStatusType::PENDING;
    $pending_order_status_id = new UnsignedInt((int)$pending_order_status_type);

    $pending_payment_status_type = PaymentStatusType::PENDING;
    $pending_payment_status_id = new UnsignedInt((int)$pending_payment_status_type);

    // Insert confirmed order into db
    $insert_confirmed_order_query_handle = $this->confirmedOrderInsertQuery->insert(
      $user_id,
      $scopes_count,
      $start_timestamp,
      $end_timestamp,
      $short_code_id,
      $server_price,
      $current_timestamp,
      $pending_order_status_id,
      $pending_payment_status_id
    );

    return $insert_confirmed_order_query_handle
      ->getWaitHandle()
      ->join();
  }
}
