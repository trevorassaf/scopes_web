<?hh // strict

class QueryException extends Exception {

  public function __construct(
    private AsyncMysqlQueryErrorResult $errorResult
  ) {
    parent::__construct($this->makeErrorMessage($this->errorResult));
  }

  private function makeErrorMessage(AsyncMysqlQueryErrorResult $error_result): string {
    return "QueryException: failure-type: " . $error_result->failureType() .
      ", mysql-errno: " . $error_result->mysql_errno() . ", mysql-error: ".
      $error_result->mysql_error(); 
  }

  public function getErrorResult(): AsyncMysqlQueryErrorResult {
    return $this->errorResult;
  }
}
