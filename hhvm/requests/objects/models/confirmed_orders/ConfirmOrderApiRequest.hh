<?hh // strict

class ConfirmOrderApiRequest {

  const string REQUEST_OBJECT_NAME = "ConfirmOrderApiRequest";

  const string SCOPES_COUNT_KEY = "scopes-count";
  const string DURATION_KEY = "duration";
  const string START_TIMESTAMP_KEY = "start-timestamp";
  const string SHORT_CODE_KEY = 'short-code';

  public function __construct(
    private RequestField<UnsignedInt> $scopesCount,
    private RequestField<Timestamp> $startTimestamp,
    private RequestField<UnsignedInt> $experimentDuration,
    private RequestField<UnsignedInt> $shortCodeId
  ) {}

  public function getScopesCount(): RequestField<UnsignedInt> {
    return $this->scopesCount;
  }

  public function getStartTimestamp(): RequestField<Timestamp> {
    return $this->startTimestamp;
  }

  public function getExperimentDuration(): RequestField<UnsignedInt> {
    return $this->experimentDuration;
  }

  public function getShortCodeId(): RequestField<UnsignedInt> {
    return $this->shortCodeId;
  }
}

class ConfirmOrderApiRequestBuilder {
  
  private ?RequestField<UnsignedInt> $scopesCount;
  private ?RequestField<Timestamp> $startTimestamp;
  private ?RequestField<UnsignedInt> $experimentDuration;
  private ?RequestField<UnsignedInt> $shortCodeId;

  public function setScopesCount(RequestField<UnsignedInt> $scopes_count): this {
    $this->scopesCount = $scopes_count;
    return $this;
  }

  public function setStartTimestamp(RequestField<Timestamp> $start_timestamp): this {
    $this->startTimestamp = $start_timestamp;
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
      $this->checkNotNull($this->startTimestamp, ConfirmOrderApiRequest::START_TIMESTAMP_KEY),
      $this->checkNotNull($this->experimentDuration, ConfirmOrderApiRequest::DURATION_KEY),
      $this->checkNotNull($this->shortCodeId, ConfirmOrderApiRequest::SHORT_CODE_KEY)
    );
  }
}
