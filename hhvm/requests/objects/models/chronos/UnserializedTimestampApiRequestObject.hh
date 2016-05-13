<?hh // strict

class UnserializedTimestampApiRequest {

  const string REQUEST_OBJECT_NAME = 'UnserializedTimestampApiRequestObject';

  const string DATE_KEY = 'date';
  const string TIME_KEY = 'time';

  public function __construct(
    private UnserializedDateApiRequest $date,
    private UnserializedTimeApiRequest $time
  ) {}

  public function getDate(): UnserializedDateApiRequest {
    return $this->date;
  }

  public function getTime(): UnserializedTimeApiRequest {
    return $this->time;
  }
}

class UnserializedTimestampApiRequestBuilder {

  private ?UnserializedDateApiRequest $date;
  private ?UnserializedTimeApiRequest $time;

  public function setDate(UnserializedDateApiRequest $date): this {
    $this->date = $date;
    return $this;
  }

  public function setTime(UnserializedTimeApiRequest $time): this {
    $this->time = $time;
    return $this;
  }

  private function checkNotNull<T>(?T $field, string $key): T {
    if ($field === null) {
      throw new UnsetRequestFieldException(
        UnserializedTimestampApiRequest::REQUEST_OBJECT_NAME,
        $key
      );
    }
    return $field;
  }

  public function build(): UnserializedTimestampApiRequest {
    return new UnserializedTimestampApiRequest(
      $this->checkNotNull(
        $this->date,
        UnserializedTimestampApiRequest::DATE_KEY
      ),
      $this->checkNotNull(
        $this->time,
        UnserializedTimestampApiRequest::TIME_KEY
      ),
    ); 
  }
}
