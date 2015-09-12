<?hh // strict

class QueryInjector {

  private ?FetchQuery<User> $fetchUserQuery;
  private ?FetchByUniqueKeyQuery<User> $fetchUserByUniqueKeyQuery;

  public function __construct(
    private LazyLoader<AsyncMysqlConnection> $asyncMysqlConnectionLazyLoader,
    private LazyLoader<ConstraintMapToConjunctiveWhereClauseTranslator> $constraintMapToConjunctiveWhereClauseTranslatorLazyLoader,
    private LazyLoader<UsersTable> $usersTableLazyLoader,
    private LazyLoader<ModelFactory<User>> $userModelFactory
  ) {}

  // User queries
  public function getInsertUserQuery(): void {}

  public function getFetchUserQuery(): FetchQuery<User> {
    if ($this->fetchUserQuery === null) {
      $this->fetchUserQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->userModelFactory->load()
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
