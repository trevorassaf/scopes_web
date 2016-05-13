<?hh // strict

class UnserializedDateApiRequest {

  const string REQUEST_OBJECT_NAME = 'UnserializedDateApiRequest';

  const string YEAR_KEY = 'year';
  const string MONTH_KEY = 'month';
  const string DATE_KEY = 'date';

  public function __construct(
    private RequestField<UnsignedInt> $year,
    private RequestField<UnsignedInt> $month,
    private RequestField<UnsignedInt> $date
  ) {}

  public function getYear(): RequestField<UnsignedInt> {
    return $this->year;
  }

  public function getMonth(): RequestField<UnsignedInt> {
    return $this->month;
  }

  public function getDate(): RequestField<UnsignedInt> {
    return $this->date;
  }
}

class UnserializedDateApiRequestBuilder {
  
  private ?RequestField<UnsignedInt> $year;
  private ?RequestField<UnsignedInt> $month;
  private ?RequestField<UnsignedInt> $date;

  public function setYear(RequestField<UnsignedInt> $year): this {
    $this->year = $year;
    return $this;
  }

  public function setMonth(RequestField<UnsignedInt> $month): this {
    $this->month = $month;
    return $this;
  }

  public function setDate(RequestField<UnsignedInt> $date): this {
    $this->date = $date;
    return $this;
  }
  
  private function checkNotNull<T>(?T $field, string $key): T {
    if ($field === null) {
      throw new UnsetRequestFieldException(
        UnserializedDateApiRequest::REQUEST_OBJECT_NAME,
        $key
      );
    }
    return $field;
  }

  public function build(): UnserializedDateApiRequest {
    return new UnserializedDateApiRequest(
      $this->checkNotNull(
        $this->year,
        UnserializedDateApiRequest::YEAR_KEY
      ),
      $this->checkNotNull(
        $this->month,
        UnserializedDateApiRequest::MONTH_KEY
      ),
      $this->checkNotNull(
        $this->date,
        UnserializedDateApiRequest::DATE_KEY
      )
    );
  }
}
