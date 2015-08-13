<?hh // strict

class AddUserMethod {

  public function __construct(
    private AsyncMysqlConnection $databaseConnection
  ) {}

  public function addUser(
    string $first_name,
    string $last_name,
    Email $email,
    string $password_hash,
  ): MethodResult {
    $method_result_builder = new MethodResultBuilder();
    return $method_result_builder->build();
  }

}
