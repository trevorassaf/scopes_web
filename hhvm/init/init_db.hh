<?hh // decl

require_once(dirname(__FILE__).'/../vendor/autoload.php');

date_default_timezone_set("America/Detroit");

async function initOrderConfiguration(
  AsyncMysqlConnection $conn,
): Awaitable<void> {
  $insert_query = new OrderConfigurationInsert(
    $conn,
    new OrderConfigurationTable()
  );

  $minutes_per_interval_count = new UnsignedInt(60);
  $price_per_interval_count = new UnsignedInt(100);
  $scopes_count = new UnsignedInt(16);

  await $insert_query->insert(
    $minutes_per_interval_count,
    $price_per_interval_count,
    $scopes_count 
  );
}

async function initAdminEdges(
  AsyncMysqlConnection $conn,
  ImmVector<User> $admin_users
): Awaitable<void> {

  $edge_insert_query = new UserPrivilegeEdgeInsert(
    $conn,
    new UsersTable(),
    new UserPrivilegesTable(),
    new UserUserPrivilegeEdgesTable()
  );

  foreach ($admin_users as $user) {
    await $edge_insert_query->insert(
      $user,
      UserPrivilege::fromType(UserPrivilegeType::ADMIN)
    );   
  }
}

async function initUserPrivileges(
  AsyncMysqlConnection $conn
): Awaitable<void> {
  $user_privileges_insert = new UserPrivilegeInsert(
    $conn,
    new UserPrivilegesTable()
  );

  // Insert privileges
  await $user_privileges_insert->insert(UserPrivilegeType::ADMIN);
}

async function initAdmins(
  AsyncMysqlConnection $conn
): Awaitable<Vector<User>> {
  $users_table = new UsersTable();
  $user_insertion_query = new UserInsertion(
    $conn,
    $users_table
  );

  $admin_users = Vector{};

  $admin_users[] = await $user_insertion_query->insert(
    "Trevor",
    "Assaf",
    new Email("astrev@umich.edu"),
    "password",
    new DateTime()
  );
  
  $admin_users[] = await $user_insertion_query->insert(
    "Alexis",
    "Donneys",
    new Email("alexisd@med.umich.edu"),
    "password",
    new DateTime()
  );
  
  $admin_users[] = await $user_insertion_query->insert(
    "Kevin",
    "LaForest",
    new Email("kmforest@umich.edu"),
    "password",
    new DateTime()
  );
  
  return $admin_users;
}

async function initDb(): Awaitable<void> {
  // Open database
  $conn = await AsyncMysqlClient::connect(
    '127.0.0.1',
    3306,
    'Scopes',
    'trevor',
    'password'
  );

  // Load default users
  $users = await initAdmins($conn); 

  // Load default user-privileges
  await initUserPrivileges($conn); 

  // Load admin user/user-privilege edges
  await initAdminEdges($conn, $users->toImmVector());

  // Load order configuration
  await initOrderConfiguration($conn);
}

initDb()->join();
