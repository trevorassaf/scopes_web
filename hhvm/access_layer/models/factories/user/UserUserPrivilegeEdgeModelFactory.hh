<?hh // strict

class UserUserPrivilegeEdgeModelFactory extends ConcreteModelFactory<UserUserPrivilegeEdge> {

  public function __construct(
    private UserUserPrivilegeEdgesTable $userUserPrivilegeEdgesTable
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): UserUserPrivilegeEdge {
    return new UserUserPrivilegeEdge(
      $id,
      new UnsignedInt((int)$params[$this->userUserPrivilegeEdgesTable->getUserIdKey()]),
      new UnsignedInt((int)$params[$this->userUserPrivilegeEdgesTable->getUserPrivilegeIdKey()]),
    );
  }
}
