<?hh // strict

class ReserveOrderRequest {

  const string REQUEST_OBJECT_NAME = "ReserveOrderRequest";

  const string USER_ID_KEY = "user-id";
  const string SCOPES_COUNT_KEY = "scopes-count";
  const string START_TIME_KEY = "start-time";
  const string END_TIME_KEY = "end-time";

  public function __construct(
    private RequestField<UnsignedInt> $userId,
    private RequestField<UnsignedInt> $scopesCount,
    private RequestField<Timestamp> $startTime,
    private RequestField<Timestamp> $endTime
  ) {}

  public function getUserId(): RequestField<UnsignedInt> {
    return $this->userId;
  }

  public function getScopesCount(): RequestField<UnsignedInt> {
    return $this->scopesCount;
  }

  public function getStartTime(): RequestField<Timestamp> {
    return $this->startTime;
  }
  
  public function getEndTime(): RequestField<Timestamp> {
    return $this->endTime;
  }
}

class ReserveOrderRequestBuilder {

  private ?RequestField<UnsignedInt> $userId;
  private ?RequestField<UnsignedInt> $scopesCount;
  private ?RequestField<Timestamp> $startTime;
  private ?RequestField<Timestamp> $endTime;

  public function setUserId(
    RequestField<UnsignedInt> $user_id
  ): this {
    $this->userId = $user_id;
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

  public function setEndTime(
    RequestField<Timestamp> $end_time
  ): this {
    $this->endTime = $end_time;
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

    if ($this->endTime == null) {
      throw new UnsetRequestFieldException(
        ReserveOrderRequest::REQUEST_OBJECT_NAME,
        ReserveOrderRequest::END_TIME_KEY
      ); 
    }

    return new ReserveOrderRequest(
      $this->userId,
      $this->scopesCount,
      $this->startTime,
      $this->endTime
    );
  }
}
