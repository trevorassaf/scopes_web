<?hh

enum UserPrivilegeType: int { 
  ADMIN = 0;
  DEV = 1;
}

class UserPrivilege implements Model {

  public function __construct(
      private UnsignedInt $id
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }
}
