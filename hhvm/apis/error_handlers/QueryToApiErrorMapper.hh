<?hh // strict

class QueryToApiErrorMapper {

  private static ImmMap<QueryErrorType, ApiErrorType> $QUERY_TO_API_ERROR_MAP = ImmMap {
  };

  public function map(QueryErrorType $query_error_type): ApiErrorType {
    return self::$QUERY_TO_API_ERROR_MAP[$query_error_type]; 
  }

  public function isMapped(QueryErrorType $query_error_type): bool {
    return self::$QUERY_TO_API_ERROR_MAP->containsKey($query_error_type); 
  }
}
