<?hh // strict

class ApiResultError extends TypedApiResult {

  const ERROR_CODES_KEY = 'error-codes';

  public function __construct(
    SerializerFactory $serializer_factory,
    private ImmSet<ApiErrorType> $apiErrors
  ) {
    parent::__construct($serializer_factory);
  }

  protected function getResultType(): ApiResultType {
    return ApiResultType::ERROR;
  }

  protected function bindParametersToSerializer(
    Serializer $serializer
  ): void {
    $serializer->addParameter(
      self::ERROR_CODES_KEY,
      $this->apiErrors->toArray() 
    );
  }
}
