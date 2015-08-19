<?hh // strict

class UsersTable extends Table<User> {

  const string TABLE_NAME = "Users";
  const string FIRST_NAME_KEY = "firstName";
  const string LAST_NAME_KEY = "lastName";
  const string EMAIL_KEY = "email";
  const string PASSWORD_KEY = "passwordHash";
  const string TIME_JOINED_KEY = "timeJoined";
  
  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): User {
    return new User(
      $id,
      (string)$params[$this->getFirstNameKey()],
      (string)$params[$this->getLastNameKey()],
      new Email((string)$params[$this->getEmailKey()]),
      (string)$params[$this->getPasswordHashKey()],
      new Timestamp((string)$params[$this->getTimeJoinedKey()])
    );
  } 

  public function getTableName(): string {
    return self::TABLE_NAME;
  }

  public function getFirstNameKey(): string {
    return self::FIRST_NAME_KEY;
  }

  public function getLastNameKey(): string {
    return self::LAST_NAME_KEY;
  }

  public function getEmailKey(): string {
    return self::EMAIL_KEY;
  }

  public function getPasswordHashKey(): string {
    return self::PASSWORD_KEY;
  }

  public function getTimeJoinedKey(): string {
    return self::TIME_JOINED_KEY;
  }
}
