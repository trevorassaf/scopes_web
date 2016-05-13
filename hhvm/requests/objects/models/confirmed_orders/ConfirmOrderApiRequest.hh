<?hh // strict

class ConfirmOrderApiRequest {

  const string REQUEST_OBJECT_NAME = "ConfirmOrderApiRequest";

  const string SCOPES_COUNT_KEY = "scopes-count";
  const string DURATION_KEY = "duration";
  const string SHORT_CODE_KEY = 'short-code-id';
  const string PRICE_KEY = "price";
  const string START_TIME_KEY = "start-time";

  public function __construct(
    private RequestField<UnsignedInt> $scopesCount,
    private RequestField<UnsignedInt> $experimentDuration,
    private RequestField<UnsignedInt> $shortCodeId,
    private RequestField<UnsignedFloat> $price,
    private UnserializedTimestampApiRequest $startTime
  ) {}

  public function getScopesCount(): RequestField<UnsignedInt> {
    return $this->scopesCount;
  }

  public function getStartTime(): UnserializedTimestampApiRequest {
    return $this->startTime;
  }

  public function getExperimentDuration(): RequestField<UnsignedInt> {
    return $this->experimentDuration;
  }

  public function getShortCodeId(): RequestField<UnsignedInt> {
    return $this->shortCodeId;
  }

  public function getPrice(): RequestField<UnsignedFloat> {
    return $this->price;
  }
}

class ConfirmOrderApiRequestBuilder {
  
  private ?RequestField<UnsignedInt> $scopesCount;
  private ?RequestField<UnsignedInt> $experimentDuration;
  private ?RequestField<UnsignedInt> $shortCodeId;
  private ?RequestField<UnsignedFloat> $price;
  private ?UnserializedTimestampApiRequest $startTime;

  public function setScopesCount(RequestField<UnsignedInt> $scopes_count): this {
    $this->scopesCount = $scopes_count;
    return $this;
  }

  public function setStartTime(UnserializedTimestampApiRequest $start_time): this {
    $this->startTime = $start_time;
    return $this;
  }

  public function setExperimentDuration(RequestField<UnsignedInt> $duration): this {
    $this->experimentDuration = $duration;
    return $this;
  }

  public function setShortCodeId(RequestField<UnsignedInt> $short_code_id): this {
    $this->shortCodeId = $short_code_id;
    return $this;
  }

  public function setPrice(RequestField<UnsignedFloat> $price): this {
    $this->price = $price;
    return $this;
  }

  private function checkNotNull<T>(?T $field, string $key): T {
    if ($field === null) {
      throw new UnsetRequestFieldException(
        ConfirmOrderApiRequest::REQUEST_OBJECT_NAME,
        $key
      );
    }
    return $field;
  }

  public function build(): ConfirmOrderApiRequest {
    // Extrude request object and ensure fields are not null
    return new ConfirmOrderApiRequest(
      $this->checkNotNull($this->scopesCount, ConfirmOrderApiRequest::SCOPES_COUNT_KEY),
      $this->checkNotNull($this->experimentDuration, ConfirmOrderApiRequest::DURATION_KEY),
      $this->checkNotNull($this->shortCodeId, ConfirmOrderApiRequest::SHORT_CODE_KEY),
      $this->checkNotNull($this->price, ConfirmOrderApiRequest::PRICE_KEY),
      $this->checkNotNull($this->startTime, ConfirmOrderApiRequest::START_TIME_KEY)
    );
  }
}
