<?hh // strict

class ApiExceptionToApiResultErrorConverter {

  public function __construct(
    private SerializerFactory $serializerFactory 
  ) {}

  public function convert(
    ApiException $api_exception
  ): ApiResultError {
    return new ApiResultError(
      $this->serializerFactory,
      ImmSet{}
    );  
  }

}
