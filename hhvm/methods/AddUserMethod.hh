<?hh // strict

class AddUserMethod {

  public function __construct(
    private UserInsertQuery $userInsertQuery
  ) {}

  public function addUser(
    string $first_name,
    string $last_name,
    Email $email,
    string $password_hash,
    MethodResultBuilder $method_result_builder
  ): User {
    try {
      $user = $this->userInsertQuery
        ->insert(
          $first_name,
          $last_name,
          $email,
          $password_hash,
          new DateTime()
        )
        ->join();
    } catch (QueryException $ex) {
      $method_error_builder = new MethodErrorBuilder(); 
      $method_result_builder->addMethodError(
        
      );
    }

    $method_result_builder = new MethodResultBuilder();
    return $method_result_builder->build();
  }
}
