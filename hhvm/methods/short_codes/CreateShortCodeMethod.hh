<?hh // strict

class CreateShortCodeMethod {

  public function __construct(
    private InsertShortCodeQuery $insertShortCodeQuery
  ) {}

  public function createShortCode(
    UnsignedInt $user_id,
    string $code,
    string $alias
  ): ShortCode {
    try {
      // Attempt insert
      $insert_query_wait_handle = $this->insertShortCodeQuery->insert(
        $user_id,
        $code,
        $alias
      ); 

      // Block until insert query finishes
      return $insert_query_wait_handle
        ->getWaitHandle()
        ->join();

    } catch (QueryException $ex) {
      switch ($ex->getErrorType()) {
        case QueryErrorType::DUPLICATE_KEY:
          throw new DuplicateShortCodeException();
          break;
        default:
          throw new FailedQueryMethodException($ex);
          break;
      }
    }
  }

}
