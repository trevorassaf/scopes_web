<?hh // strict

class CreateUserPrivilegesMethod {

  private static ImmMap<UserPrivilegeType, string> $USER_PRIVILEGE_MAP = ImmMap{
    UserPrivilegeType::ADMIN => "admin",
    UserPrivilegeType::DEVELOPER => "developer",
    UserPrivilegeType::TECHNICIAN => "tecnician",
  };

  public function __construct(
    private InsertUserPrivilegeQuery $insertQuery
  ) {}

  public function createUserPrivileges(): void {
    try {
      foreach (self::$USER_PRIVILEGE_MAP as $privilege_type => $privilege_name) {
        $query_handle = $this->insertQuery->insert($privilege_type, $privilege_name); 
        $query_handle
          ->getWaitHandle()
          ->join();
      }   
    } catch (QueryException $ex) {
      switch ($ex->getErrorType()) {
        case QueryErrorType::DUPLICATE_KEY:
          throw new DuplicateEmailException();
          break;
        default:
          throw new FailedQueryMethodException($ex);
          break;
      } 
    }
  }
}
