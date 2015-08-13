<?hh // strict

class QueryToApiExceptionConverter {

  public function __construct(
      private QueryToApiErrorFilter $queryToApiErrorFilter    
  ) {}

  public function convert(
    QueryException $query_exception
  ): ApiException {
    return new ApiException(
      $this->queryToApiErrorFilter->filter(
        $query_exception->getQueryErrorTypes()
      )
    );
  }
}
