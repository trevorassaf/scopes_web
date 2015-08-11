<?hh // strict

class UsersTable {

  const string TABLE_NAME = "Users";
  const string ID_KEY = "id";
  const string FIRST_NAME_KEY = "firstName";
  const string LAST_NAME_KEY = "lastName";
  const string EMAIL_KEY = "email";
  const string PASSWORD_KEY = "passwordHash";
  const string TIME_JOINED_KEY = "timeJoined";
  
  public function extrude(Map<string, string> $params): User {
    return new User(
      new UnsignedInt((int)$params[$this->getIdKey()]),
      $params[$this->getFirstNameKey()],
      $params[$this->getLastNameKey()],
      new Email($params[$this->getEmailKey()]),
      $params[$this->getPasswordHashKey()],
      new DateTime($params[$this->getTimeJoinedKey()])
    );
  } 

  public function getTableName(): string {
    return self::TABLE_NAME;
  }

  public function getIdKey(): string {
    return self::ID_KEY;
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
