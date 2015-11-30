<?hh // strict

class UserUserPrivilegeEdge implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $userId,
    private UnsignedInt $userPrivilegeId
  ) {}  

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getUserId(): UnsignedInt {
    return $this->userId;
  }

  public function getUserPrivilegeId(): UnsignedInt {
    return $this->userPrivilegeId;
  }
}
