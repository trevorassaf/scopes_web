<?hh // strict

class AssignUserPrivilegesMethod {

  public function __construct(
    private InsertUserUserPrivilegeEdgeQuery $insertEdgeQuery
  ) {}

  public function assignPrivilege(
    UnsignedInt $user_id,
    UserPrivilegeType $privilege_type
  ): void {
    try {
      $insert_handle = $this->insertEdgeQuery->insert(
        $user_id,
        new UnsignedInt((int)$privilege_type)
      );    

      $insert_handle
        ->getWaitHandle()
        ->join();

    } catch (QueryException $ex) {
      switch ($ex->getErrorType()) {
        case QueryErrorType::DUPLICATE_KEY:
          break;
        default:
          throw new FailedQueryMethodException($ex);
          break;
      }
    }
  }

  public function assignPrivileges(
    UnsignedInt $user_id,
    ImmSet<UserPrivilegeType> $privilege_types
  ): void {
    foreach ($privilege_types as $type) {
      $this->assignPrivilege($user_id, $type);
    }
  }
}
