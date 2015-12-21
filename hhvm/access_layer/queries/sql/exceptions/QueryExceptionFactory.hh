<?hh // strict

class QueryExceptionFactory {

  private static ImmMap<int, QueryErrorType> $ASYNC_QUERY_ERROR_MAP = ImmMap{
    1062 => QueryErrorType::DUPLICATE_KEY 
  };

  public function make(AsyncMysqlQueryException $exception): QueryException {
    $query_error_code = $this->convertToErrorType($exception); 
    $derived_exception = null; 

    switch ($query_error_code) {
      case QueryErrorType::DUPLICATE_KEY:
        $derived_exception = new DuplicateUniqueKeyQueryException(
          $exception->mysqlErrorString()
        );    
        break;
      default:
        invariant(
          false,
          "QueryExceptionFactory:: shouldn't happen, we're not catching query error: "
            . (string)$exception->mysqlErrorCode() . ", with error string: "
            . $exception->mysqlErrorString()
        );
        break;
    }

    return $derived_exception;
  }

  private function convertToErrorType(AsyncMysqlQueryException $ex): QueryErrorType {
    if (self::$ASYNC_QUERY_ERROR_MAP->contains($ex->mysqlErrorCode())) {
      return self::$ASYNC_QUERY_ERROR_MAP[$ex->mysqlErrorCode()]; 
    }
    return QueryErrorType::UNKNOWN;
  }
}
