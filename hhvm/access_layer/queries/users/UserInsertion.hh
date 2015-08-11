<?hh // strict

require_once(dirname(__FILE__)."/../../tables/UsersTable.hh");
require_once(dirname(__FILE__)."/../../models/User.hh");

class UserInsertion {

  public function __construct(
      private AsyncMysqlConnection $asyncMysqlConnection,
      private UsersTable $usersTable
  ) {}

  public async function insert(User $user): Awaitable<void> {
    echo "Insertion query: " . $this->createQuery($user) . "\n";
    await $this->asyncMysqlConnection->query(
      $this->createQuery($user)
    );  
  }

  public function createQuery(User $user): string {
    return 
      "INSERT INTO " . $this->usersTable->getTableName() . " ("
        . $this->usersTable->getIdKey() . ", "
        . $this->usersTable->getFirstNameKey() . ", "
        . $this->usersTable->getLastNameKey() . ", "
        . $this->usersTable->getEmailKey() . ", "
        . $this->usersTable->getPasswordHashKey() . ", "
        . $this->usersTable->getTimeJoinedKey() 
      . ") VALUES ("
        . $user->getId()->getNumber() . ", '"
        . $user->getFirstName() . "', '"
        . $user->getLastName() . "', '"
        . $user->getEmail()->toString() . "', '"
        . $user->getPasswordHash() . "', '"
        . $user->getTimeJoined()->format('Y-m-d H:i:s')
      . "')";
  }
}
