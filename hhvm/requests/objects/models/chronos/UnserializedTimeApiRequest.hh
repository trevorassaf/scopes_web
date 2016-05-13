<?hh // strict

class UnserializedTimeApiRequest {

  const string REQUEST_OBJECT_NAME = 'UnserializedTimeApiRequest';

  const string HOURS_KEY = 'hours';
  const string MINUTES_KEY = 'minutes';
  const string SECONDS_KEY = 'seconds';

  public function __construct(
    private RequestField<UnsignedInt> $hours,
    private RequestField<UnsignedInt> $minutes,
    private RequestField<UnsignedInt> $seconds
  ) {}

  public function getHours(): RequestField<UnsignedInt> {
    return $this->hours;
  }
  
  public function getMinutes(): RequestField<UnsignedInt> {
    return $this->minutes;
  }

  public function getSeconds(): RequestField<UnsignedInt> {
    return $this->seconds;
  }
}

class UnserializedTimeApiRequestBuilder {

  private ?RequestField<UnsignedInt> $hours;
  private ?RequestField<UnsignedInt> $minutes;
  private ?RequestField<UnsignedInt> $seconds;

  public function setHours(RequestField<UnsignedInt> $hours): this {
    $this->hours = $hours;
    return $this;
  }

  public function setMinutes(RequestField<UnsignedInt> $minutes): this {
    $this->minutes = $minutes;
    return $this;
  }

  public function setSeconds(RequestField<UnsignedInt> $seconds): this {
    $this->seconds = $seconds;
    return $this;
  }

  private function checkNotNull<T>(?T $field, string $key): T {
    if ($field === null) {
      throw new UnsetRequestFieldException(
        UnserializedTimeApiRequest::REQUEST_OBJECT_NAME,
        $key
      );
    }
    return $field;
  }

  public function build(): UnserializedTimeApiRequest {
    return new UnserializedTimeApiRequest(
      $this->checkNotNull(
        $this->hours,
        UnserializedTimeApiRequest::HOURS_KEY
      ),
      $this->checkNotNull(
        $this->minutes,
        UnserializedTimeApiRequest::MINUTES_KEY
      ),
      $this->checkNotNull(
        $this->seconds,
        UnserializedTimeApiRequest::SECONDS_KEY
      )
    );    
  }
}
