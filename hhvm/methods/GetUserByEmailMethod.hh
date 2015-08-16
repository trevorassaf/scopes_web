<?hh // strict

class GetUserByEmailMethod {

  public function __construct(
    private QueryToApiExceptionConverter $queryToApiExceptionConverter,
    private GetUserByEmailQuery $getUserByEmailQuery
  ) {}

  public function getUser(Email $email): User {
    $user = null;
    try {
      $query_wait_handle = $this
        ->getUserByEmailQuery
        ->get($email);  
      $user = $query_wait_handle
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {
      throw $this->queryToApiExceptionConverter->convert($ex); 
    } 

    // Raise error because the email didn't match a user
    if ($user == null) {
      // TODO return error indicating no user found
      /*
      $api_exception_builder = new ApiExceptionBuilder();
      throw $api_exception_builder
        ->addApiError(ApiErrorType::FETCH_MISS)
        ->build();
       */
      $api_exception_builder = new ApiExceptionBuilder();
      throw $api_exception_builder->build();
    }

    return $user;
  }
}
