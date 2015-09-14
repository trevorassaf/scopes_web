<?hh // strict

class QueryInjector {

  // User queries
  private ?InsertQuery<User> $insertUserQuery;
  private ?InsertUserQuery $concreteInsertUserQuery;
  private ?FetchQuery<User> $fetchUserQuery;
  private ?FetchByUniqueKeyQuery<User> $fetchUserByUniqueKeyQuery;

  // Regular Day Queries
  private ?InsertQuery<RegularWeekDay> $insertRegularWeekDayQuery;
  private ?InsertRegularWeekDayQuery $concreteInsertRegularWeekDayQuery;
  private ?FetchByIdQuery<RegularWeekDay> $fetchRegularWeekDayByIdQuery;
  private ?FetchByUniqueKeyQuery<RegularWeekDay> $fetchRegularWeekDayByUniqueKeyQuery;
  private ?FetchQuery<RegularWeekDay> $fetchRegularWeekDayQuery;

  // Regular Time Queries
  private ?InsertQuery<RegularTime> $insertRegularTimeQuery;
  private ?InsertRegularTimeQuery $concreteInsertRegularTimeQuery;
  private ?FetchQuery<RegularTime> $fetchRegularTimeQuery;
  private ?FetchByUniqueKeyQuery<RegularTime> $fetchRegularTimeByUniqueKeyQuery;

  // Regular week day/time edges
  private ?InsertQuery<RegularWeekDayRegularTimeEdge> $insertRegularEdgeQuery;
  private ?InsertRegularWeekDayRegularTimeEdgeQuery $concreteInsertRegularEdgeQuery;
  private ?FetchQuery<RegularWeekDayRegularTimeEdge> $fetchRegularEdgeQuery;
  private ?FetchByUniqueKeyQuery<RegularWeekDayRegularTimeEdge> $fetchRegularEdgeByUniqueKeyQuery;

  public function __construct(
    private LazyLoader<AsyncMysqlConnection> $asyncMysqlConnectionLazyLoader,
    private LazyLoader<ConstraintMapToConjunctiveWhereClauseTranslator> $constraintMapToConjunctiveWhereClauseTranslatorLazyLoader,
    private LazyLoader<UsersTable> $usersTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<User>> $userModelFactoryLazyLoader,
    private LazyLoader<InsertQueryCreater> $insertQueryCreaterLazyLoader,
    private LazyLoader<RegularWeekDaysTable> $regularWeekDaysTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<RegularWeekDay>> $regularWeekDayModelFactoryLazyLoader,
    private LazyLoader<RegularTimesTable> $regularTimesTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<RegularTime>> $regularTimeModelFactoryLazyLoader,
    private LazyLoader<RegularWeekDayRegularTimeEdgesTable> $regularEdgesTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<RegularWeekDayRegularTimeEdge>> $regularEdgeModelFactoryLazyLoader
  ) {}

  /**
   * User queries
   */
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

  /**
   * Date/Time queries
   */
  public function getInsertRegularWeekDayQuery(): InsertQuery<RegularWeekDay> {
    if ($this->insertRegularWeekDayQuery === null) {
      $this->insertRegularWeekDayQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->regularWeekDaysTableLazyLoader->load(),
        $this->regularWeekDayModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load()
      );
    } 
    return $this->insertRegularWeekDayQuery;
  }

  public function getConcreteInsertRegularWeekDayQuery(): InsertRegularWeekDayQuery {
    if ($this->concreteInsertRegularWeekDayQuery === null) {
      $this->concreteInsertRegularWeekDayQuery = new InsertRegularWeekDayQuery(
        $this->getInsertRegularWeekDayQuery(),
        $this->regularWeekDaysTableLazyLoader->load()
      );
    }
    return $this->concreteInsertRegularWeekDayQuery;
  }

  public function getFetchRegularWeekDayQuery(): FetchQuery<RegularWeekDay> {
    if ($this->fetchRegularWeekDayQuery === null) {
      $this->fetchRegularWeekDayQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->regularWeekDayModelFactoryLazyLoader->load()
      );
    }
    return $this->fetchRegularWeekDayQuery;
  }

  public function getFetchRegularWeekDayByUniqueKeyQuery(): FetchByUniqueKeyQuery<RegularWeekDay> {
    if ($this->fetchRegularWeekDayByUniqueKeyQuery === null) {
      $this->fetchRegularWeekDayByUniqueKeyQuery = new FetchByUniqueKeyQuery(
        $this->getFetchRegularWeekDayQuery(),
        $this->regularWeekDaysTableLazyLoader->load(),
        $this->constraintMapToConjunctiveWhereClauseTranslatorLazyLoader->load()
      );
    } 
    return $this->fetchRegularWeekDayByUniqueKeyQuery;
  }

  public function getFetchRegularWeekDayByIdQuery(): FetchByIdQuery<RegularWeekDay> {
    if ($this->fetchRegularWeekDayByIdQuery === null) {
      $this->fetchRegularWeekDayByIdQuery = new FetchByIdQuery(
        $this->getFetchRegularWeekDayByUniqueKeyQuery(),
        $this->regularWeekDaysTableLazyLoader->load()
      );
    }
    return $this->fetchRegularWeekDayByIdQuery;
  }

  // Regular time queries
  public function getInsertRegularTimeQuery(): InsertQuery<RegularTime> {
    if ($this->insertRegularTimeQuery === null) {
      $this->insertRegularTimeQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->regularTimesTableLazyLoader->load(),
        $this->regularTimeModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load()
      );
    }
    return $this->insertRegularTimeQuery;
  }

  public function getConcreteInsertRegularTimeQuery(): InsertRegularTimeQuery {
    if ($this->concreteInsertRegularTimeQuery === null) {
      $this->concreteInsertRegularTimeQuery = new InsertRegularTimeQuery(
        $this->getInsertRegularTimeQuery(),
        $this->regularTimesTableLazyLoader->load()
      );
    }
    return $this->concreteInsertRegularTimeQuery;
  }

  public function getFetchRegularTimeByUniqueKeyQuery(): FetchByUniqueKeyQuery<RegularTime> {
    if ($this->fetchRegularTimeByUniqueKeyQuery === null) {
      $this->fetchRegularTimeByUniqueKeyQuery = new FetchByUniqueKeyQuery(
        $this->getFetchRegularTimeQuery(),
        $this->regularTimesTableLazyLoader->load(),
        $this->constraintMapToConjunctiveWhereClauseTranslatorLazyLoader->load() 
      );
    }
    return $this->fetchRegularTimeByUniqueKeyQuery;
  }

  public function getFetchRegularTimeQuery(): FetchQuery<RegularTime> {
    if ($this->fetchRegularTimeQuery === null) {
      $this->fetchRegularTimeQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->regularTimeModelFactoryLazyLoader->load()
      );
    }
    return $this->fetchRegularTimeQuery;
  }

  // Regular week day/time edge queries
  public function getInsertRegularEdgeQuery(): InsertQuery<RegularWeekDayRegularTimeEdge> {
    if ($this->insertRegularEdgeQuery === null) {
      $this->insertRegularEdgeQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->regularEdgesTableLazyLoader->load(),
        $this->regularEdgeModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load()
      );
    }
    return $this->insertRegularEdgeQuery;
  }

  public function getConcreteInsertRegularEdgeQuery(): InsertRegularWeekDayRegularTimeEdgeQuery {
    if ($this->concreteInsertRegularEdgeQuery === null) {
      $this->concreteInsertRegularEdgeQuery = new InsertRegularWeekDayRegularTimeEdgeQuery(
        $this->getInsertRegularEdgeQuery(),
        $this->regularEdgesTableLazyLoader->load() 
      );
    }    
    return $this->concreteInsertRegularEdgeQuery;
  }

  public function getFetchRegularEdgeQuery(): FetchQuery<RegularWeekDayRegularTimeEdge> {
    if ($this->fetchRegularEdgeQuery === null) {
      $this->fetchRegularEdgeQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->regularEdgeModelFactoryLazyLoader->load()  
      ); 
    }
    return $this->fetchRegularEdgeQuery;
  }

  public function getFetchRegularEdgeByUniqueKeyQuery(): FetchByUniqueKeyQuery<RegularWeekDayRegularTimeEdge> {
    if ($this->fetchRegularEdgeByUniqueKeyQuery === null) {
      $this->fetchRegularEdgeByUniqueKeyQuery = new FetchByUniqueKeyQuery(
        $this->getFetchRegularEdgeQuery(),
        $this->regularEdgesTableLazyLoader->load(),
        $this->constraintMapToConjunctiveWhereClauseTranslatorLazyLoader->load()  
      );
    }
    return $this->fetchRegularEdgeByUniqueKeyQuery;
  }
}
