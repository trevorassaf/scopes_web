<?hh // strict

class QueryInjector {

  private ?InsertQuery<User> $insertUserQuery;
  private ?InsertUserQuery $concreteInsertUserQuery;
  private ?FetchQuery<User> $fetchUserQuery;
  private ?FetchByUniqueKeyQuery<User> $fetchUserByUniqueKeyQuery;

  public function __construct(
    private LazyLoader<AsyncMysqlConnection> $asyncMysqlConnectionLazyLoader,
    private LazyLoader<ConstraintMapToConjunctiveWhereClauseTranslator> $constraintMapToConjunctiveWhereClauseTranslatorLazyLoader,
    private LazyLoader<UsersTable> $usersTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<User>> $userModelFactoryLazyLoader,
    private LazyLoader<InsertQueryCreater> $insertQueryCreaterLazyLoader
  ) {}

  // User queries
  public function getInsertUserQuery(): InsertQuery<User> {
    if ($this->insertUserQuery === null) {
      $this->insertUserQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->usersTableLazyLoader->load(),
        $this->userModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load() 
      );
    }  
    return $this->insertUserQuery;
  }

  public function getConcreteInsertUserQuery(): InsertUserQuery {
    if ($this->concreteInsertUserQuery === null) {
      $this->concreteInsertUserQuery = new InsertUserQuery(
        $this->getInsertUserQuery(),
        $this->usersTableLazyLoader->load()
      );
    }
    return $this->concreteInsertUserQuery;
  }

  public function getFetchUserQuery(): FetchQuery<User> {
    if ($this->fetchUserQuery === null) {
      $this->fetchUserQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->userModelFactoryLazyLoader->load()
      );
    }
    return $this->fetchUserQuery;
  }

  public function getFetchUserByUniqueKeyQuery(): FetchByUniqueKeyQuery<User> {
    if ($this->fetchUserByUniqueKeyQuery === null) {
      $this->fetchUserByUniqueKeyQuery = new FetchByUniqueKeyQuery(
        $this->getFetchUserQuery(),
        $this->usersTableLazyLoader->load(),
        $this->constraintMapToConjunctiveWhereClauseTranslatorLazyLoader->load()
      );
    }
    return $this->fetchUserByUniqueKeyQuery;
  }
}
