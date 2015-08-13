<?hh // strict

class QueryToApiErrorFilter {

  public function __construct(
    private QueryToApiErrorMapper $queryToApiErrorMapper      
  ) {}

  public function filter(
    ImmSet<QueryErrorType> $query_error_types
  ): ImmSet<ApiErrorType> {
    $api_error_types = Set{}; 
    
    foreach ($query_error_types as $query_error_type) {
      if ($this->queryToApiErrorMapper->isMapped($query_error_type)) {
        $api_error_types[] =
            $this->queryToApiErrorMapper->map($query_error_type);
      }
    }

    return $api_error_types->toImmSet();
  }
}
