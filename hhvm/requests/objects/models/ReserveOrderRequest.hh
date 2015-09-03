<?hh // strict

class ReserveOrderRequest {

  const string REQUEST_OBJECT_NAME = "ReserveOrderRequest";

  const string USER_ID_KEY = "user-id";
  const string LEASE_START_KEY = "lease-start";
  const string SCOPES_COUNT_KEY = "scopes-count";
  const string START_TIME_KEY = "start-time";
  const string RSVD_MIN_COUNT_KEY = "rmc";

  public function __construct(
    private RequestField<UnsignedInt> $userId,
    private RequestField<Timestamp> $leaseStart,
    private RequestField<UnsignedInt> $scopesCount,
    private RequestField<Timestamp> $startTime,
    private RequestField<UnsignedInt> $reservedMinutesCount
  ) {}

  public function getUserId(): RequestField<UnsignedInt> {
    return $this->userId;
  }

  public function getLeaseStart(): RequestField<Timestamp> {
    return $this->leaseStart;
  }

  public function getScopesCount(): RequestField<UnsignedInt> {
    return $this->scopesCount;
  }

  public function getStartTime(): RequestField<Timestamp> {
    return $this->startTime;
  }

  public function getReservedMinutesCount(): RequestField<UnsignedInt> {
    return $this->reservedMinutesCount;
  }
}

class ReserveOrderRequestBuilder {

  private ?RequestField<UnsignedInt> $userId;
  private ?RequestField<Timestamp> $leaseStart;
  private ?RequestField<UnsignedInt> $scopesCount;
  private ?RequestField<Timestamp> $startTime;
  private ?RequestField<UnsignedInt> $reservedMinutesCount;

  public function setUserId(
    RequestField<UnsignedInt> $user_id
  ): this {
    $this->userId = $user_id;
    return $this;
  }

  public function setLeaseStart(
    RequestField<Timestamp> $lease_start
  ): this {
    $this->leaseStart = $lease_start;
    return $this;
  }

  public function setScopesCount(
    RequestField<UnsignedInt> $scopes_count
  ): this {
    $this->scopesCount = $scopes_count;
    return $this;
  }

  public function setStartTime(
    RequestField<Timestamp> $start_time
  ): this {
    $this->startTime = $start_time;
    return $this;
  }

  public function setReservedMinutesCount(
    RequestField<UnsignedInt> $rsvd_min_count
  ): this {
    $this->reservedMinutesCount = $rsvd_min_count;
    return $this;
  }

  public function build(): ReserveOrderRequest {
    // Check for missing request keys
    if ($this->userId == null) {
      throw new UnsetRequestFieldException(
        ReserveOrderRequest::REQUEST_OBJECT_NAME,
        ReserveOrderRequest::USER_ID_KEY
      ); 
    }

    if ($this->leaseStart == null) {
      throw new UnsetRequestFieldException(
        ReserveOrderRequest::REQUEST_OBJECT_NAME,
        ReserveOrderRequest::LEASE_START_KEY
      ); 
    }

    if ($this->scopesCount == null) {
      throw new UnsetRequestFieldException(
        ReserveOrderRequest::REQUEST_OBJECT_NAME,
        ReserveOrderRequest::SCOPES_COUNT_KEY
      ); 
    }

    if ($this->startTime == null) {
      throw new UnsetRequestFieldException(
        ReserveOrderRequest::REQUEST_OBJECT_NAME,
        ReserveOrderRequest::START_TIME_KEY
      ); 
    }

    if ($this->reservedMinutesCount == null) {
      throw new UnsetRequestFieldException(
        ReserveOrderRequest::REQUEST_OBJECT_NAME,
        ReserveOrderRequest::RSVD_MIN_COUNT_KEY
      ); 
    }

    return new ReserveOrderRequest(
      $this->userId,
      $this->leaseStart,
      $this->scopesCount,
      $this->startTime,
      $this->reservedMinutesCount
    );
  }
}
