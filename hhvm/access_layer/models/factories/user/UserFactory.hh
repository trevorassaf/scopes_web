<?hh // strict

class UserFactory extends ConcreteModelFactory<User> {

  public function __construct(
    private TimestampSerializer $timestampSerializer,
    private UsersTable $usersTable
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): User {
    return new User(
      $id,
      (string)$params[$this->usersTable->getFirstNameKey()],
      (string)$params[$this->usersTable->getLastNameKey()],
      new Email((string)$params[$this->usersTable->getEmailKey()]),
      $this->timestampSerializer->deserialize((string)$params[$this->usersTable->getTimeJoinedKey()])
    );
  } 
}
