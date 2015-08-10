<?hh

enum UserPrivilegeType: int { 
  ADMIN = 0;
  DEV = 1;
}

class UserPrivilege {

  public function __construct(
      private UserPrivilegeType $type
  ) {}  

  public function getType(): UserPrivilegeType {
    return $this->type;
  }
}
