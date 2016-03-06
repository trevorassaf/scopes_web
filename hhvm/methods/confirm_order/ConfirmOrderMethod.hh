<?hh // strict

class ConfirmOrderMethod {

  public function __construct(
    private FetchIsUserOwnedShortCodeQuery $fetchIsUserOwnedShortCodeQuery,
    private InsertConfirmedOrderQuery $confirmedOrderInsertQuery,
    private IsValidReservedOrderMethod $isValidReservedOrderMethod,
    private IsConflictingConfirmedOrderMethod $isConflictingConfirmedOrderMethod,
    private TimestampSegmentFactory $timestampSegmentFactory,
    private TimestampBuilder $timestampBuilder,
    private TimestampOperator $timestampOperator
  ) {}

  public function confirm(
    UnsignedInt $user_id,
    UnsignedInt $scopes_count,
    Timestamp $start_timestamp,
    UnsignedInt $experiment_duration,
    UnsignedInt $short_code_id  
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

    if (!$this->isValidReservedOrderMethod->check(
      $scopes_count,
      $experiment_timestamp_segment)
    ) {
      throw new InvalidReservedOrderRequestException();
    }

    // Fail if this experiment overbooks our scopes
     
    

    // Insert confirmed order into db
    $insert_confirmed_order_query_handle = $this->confirmedOrderInsertQuery->insert(
      $user_id,
      $scopes_count,
      $start_timestamp,
      $end_timestamp,
      $short_code_id,
      new UnsignedFloat(0.0),
      $this->timestampBuilder->now()
    );

    return $insert_confirmed_order_query_handle
      ->getWaitHandle()
      ->join();
  }
}
