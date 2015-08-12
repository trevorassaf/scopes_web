<?hh // strict

require_once('Model.hh');

require_once(dirname(__FILE__)."/../../utils/data_types/UnsignedInt.hh");

enum UserPrivilegeType: int { 
  ADMIN = 0;
}

class UserPrivilege implements Model {

  public static function fromType(
    UserPrivilegeType $type
  ): UserPrivilege {
    return new UserPrivilege(new UnsignedInt((int)$type));
  }

  public function __construct(
    private UnsignedInt $id
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getType(): UserPrivilegeType {
    return UserPrivilegeType::assert($this->id->getNumber());
  }
}
