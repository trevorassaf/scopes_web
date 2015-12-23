<?hh // strict

class UsersTable extends Table {

  const string TABLE_NAME = "Users";
  const string FIRST_NAME_KEY = "firstName";
  const string LAST_NAME_KEY = "lastName";
  const string EMAIL_KEY = "email";
  const string TIME_JOINED_KEY = "timeJoined";
  
  public function getName(): string {
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

  public function getTimeJoinedKey(): string {
    return self::TIME_JOINED_KEY;
  }
}
