<?hh // strict

class UserPrivilegeFactory extends ConcreteModelFactory<UserPrivilege> {

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): UserPrivilege {
    return new UserPrivilege(
      $id
    );
  }
}
