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

  // Irregular time/day queries
  private ?InsertQuery<IrregularTime> $insertIrregularTimeQuery;
  private ?InsertQuery<IrregularDate> $insertIrregularDateQuery;
  private ?InsertIrregularTimeQuery $concreteInsertIrregularTimeQuery;
  private ?InsertIrregularDateQuery $concreteInsertIrregularDateQuery;
  private ?FetchQuery<IrregularTime> $fetchIrregularTimeQuery;
  private ?FetchQuery<IrregularDate> $fetchIrregularDateQuery;
  private ?FetchByUniqueKeyQuery<IrregularTime> $fetchIrregularTimeByUniqueKeyQuery;
  private ?FetchByUniqueKeyQuery<IrregularDate> $fetchIrregularDateByUniqueKeyQuery;
  private ?FetchIrregularTimesQuery $concreteFetchIrregularTimesQuery;

  // Reserved orders queries
  private ?FetchQuery<RsvdOrder> $fetchRsvdOrderQuery;
  private ?FetchReservedOrdersByTimeQuery $fetchRsvdOrdersByTimeQuery;
  private ?InsertQuery<RsvdOrder> $insertRsvdOrderQuery;
  private ?InsertReservedOrderQuery $concreteInsertRsvdOrderQuery;

  // Confirmed orders queries
  private ?FetchQuery<ConfirmedOrder> $fetchConfirmedOrderQuery;
  private ?FetchConfirmedOrdersByTimeQuery $fetchConfirmedOrdersByTimeQuery;
  private ?InsertQuery<ConfirmedOrder> $insertConfirmedOrderQuery;
  private ?InsertConfirmedOrderQuery $concreteInsertConfirmedOrderQuery;

  // Reserved order policy queries
  private ?FetchSingletonQuery<ReservedOrderPolicy> $fetchSingletonRsvdOrderPolicyQuery;

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
    private LazyLoader<ConcreteModelFactory<RegularWeekDayRegularTimeEdge>> $regularEdgeModelFactoryLazyLoader,
    private LazyLoader<IrregularDatesTable> $irregularDatesTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<IrregularDate>> $irregularDateModelFactoryLazyLoader,
    private LazyLoader<IrregularTimesTable> $irregularTimesTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<IrregularTime>> $irregularTimeModelFactoryLazyLoader,
    private LazyLoader<RsvdOrdersTable> $rsvdOrdersTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<RsvdOrder>> $rsvdOrderModelFactoryLazyLoader,
    private LazyLoader<ConfirmedOrdersTable> $confirmedOrdersTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<ConfirmedOrder>> $confirmedOrderModelFactoryLazyLoader,
    private LazyLoader<ReservedOrderPolicyTable> $rsvdOrderPolicyTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<ReservedOrderPolicy>> $rsvdOrderPolicyModelFactoryLazyLoader
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

  /**
   * Irregular date queries
   */
  public function getFetchIrregularDateQuery(): FetchQuery<IrregularDate> {
    if ($this->fetchIrregularDateQuery === null) {
      $this->fetchIrregularDateQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->irregularDateModelFactoryLazyLoader->load() 
      ); 
    }
    return $this->fetchIrregularDateQuery;
  }
  
  public function getFetchIrregularDateByUniqueKeyQuery(): FetchByUniqueKeyQuery<IrregularDate> {
    if ($this->fetchIrregularDateByUniqueKeyQuery === null) {
      $this->fetchIrregularDateByUniqueKeyQuery = new FetchByUniqueKeyQuery(
        $this->getFetchIrregularDateQuery(),
        $this->irregularDatesTableLazyLoader->load(),
        $this->constraintMapToConjunctiveWhereClauseTranslatorLazyLoader->load() 
      ); 
    }
    return $this->fetchIrregularDateByUniqueKeyQuery;
  }

  public function getInsertIrregularDateQuery(): InsertQuery<IrregularDate> {
    if ($this->insertIrregularDateQuery === null) {
      $this->insertIrregularDateQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->irregularDatesTableLazyLoader->load(),
        $this->irregularDateModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load()
      ); 
    }
    return $this->insertIrregularDateQuery;
  }
  
  public function getConcreteInsertIrregularDateQuery(): InsertIrregularDateQuery {
    if ($this->concreteInsertIrregularDateQuery === null) {
      $this->concreteInsertIrregularDateQuery = new InsertIrregularDateQuery(
        $this->getInsertIrregularDateQuery(),
        $this->irregularDatesTableLazyLoader->load()  
      ); 
    }
    return $this->concreteInsertIrregularDateQuery;
  }

  /**
   * Irregular time queries
   */
  public function getFetchIrregularTimeQuery(): FetchQuery<IrregularTime> {
    if ($this->fetchIrregularTimeQuery === null) {
      $this->fetchIrregularTimeQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->irregularTimeModelFactoryLazyLoader->load() 
      ); 
    }
    return $this->fetchIrregularTimeQuery;
  }

  public function getConcreteFetchIrregularTimeQuery(): FetchIrregularTimesQuery {
    if ($this->concreteFetchIrregularTimesQuery === null) {
      $this->concreteFetchIrregularTimesQuery = new FetchIrregularTimesQuery(
        $this->getFetchIrregularTimeQuery(),
        $this->irregularTimesTableLazyLoader->load() 
      ); 
    }
   return $this->concreteFetchIrregularTimesQuery; 
  }

  public function getFetchIrregularTimeByUniqueKeyQuery(): FetchByUniqueKeyQuery<IrregularTime> {
    if ($this->fetchIrregularTimeByUniqueKeyQuery === null) {
      $this->fetchIrregularTimeByUniqueKeyQuery = new FetchByUniqueKeyQuery(
        $this->getFetchIrregularTimeQuery(),
        $this->irregularTimesTableLazyLoader->load(),
        $this->constraintMapToConjunctiveWhereClauseTranslatorLazyLoader->load() 
      ); 
    }
    return $this->fetchIrregularTimeByUniqueKeyQuery;
  }

  public function getInsertIrregularTimeQuery(): InsertQuery<IrregularTime> {
    if ($this->insertIrregularTimeQuery === null) {
      $this->insertIrregularTimeQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->irregularTimesTableLazyLoader->load(),
        $this->irregularTimeModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load()
      ); 
    }
    return $this->insertIrregularTimeQuery;
  }

  public function getConcreteInsertIrregularTimeQuery(): InsertIrregularTimeQuery {
    if ($this->concreteInsertIrregularTimeQuery === null) {
      $this->concreteInsertIrregularTimeQuery = new InsertIrregularTimeQuery(
        $this->getInsertIrregularTimeQuery(),
        $this->irregularTimesTableLazyLoader->load()  
      ); 
    }
    return $this->concreteInsertIrregularTimeQuery;
  }

  /**
   * Reserved order queries.
   */
  public function getFetchRsvdOrderQuery(): FetchQuery<RsvdOrder> {
    if ($this->fetchRsvdOrderQuery === null) {
      $this->fetchRsvdOrderQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->rsvdOrderModelFactoryLazyLoader->load()
      );
    }
    return $this->fetchRsvdOrderQuery;
  }

  public function getFetchRsvdOrdersByTimeQuery(): FetchReservedOrdersByTimeQuery {
    if ($this->fetchRsvdOrdersByTimeQuery === null) {
      $this->fetchRsvdOrdersByTimeQuery = new FetchReservedOrdersByTimeQuery(
        $this->getFetchRsvdOrderQuery(), 
        $this->rsvdOrdersTableLazyLoader->load()
      );
    }
    return $this->fetchRsvdOrdersByTimeQuery;
  }

  public function getInsertRsvdOrderQuery(): InsertQuery<RsvdOrder> {
    if ($this->insertRsvdOrderQuery === null) {
      $this->insertRsvdOrderQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->rsvdOrdersTableLazyLoader->load(),
        $this->rsvdOrderModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load()
      ); 
    }
    return $this->insertRsvdOrderQuery;
  }

  public function getConcreteInsertRsvdOrderQuery(): InsertReservedOrderQuery {
    if ($this->concreteInsertRsvdOrderQuery === null) {
      $this->concreteInsertRsvdOrderQuery = new InsertReservedOrderQuery(
        $this->getInsertRsvdOrderQuery(),
        $this->rsvdOrdersTableLazyLoader->load() 
      );
    }
    return $this->concreteInsertRsvdOrderQuery;
  }

  /**
   * Confirmed order queries
   */
  public function getFetchConfirmedOrderQuery(): FetchQuery<ConfirmedOrder> {
    if ($this->fetchConfirmedOrderQuery === null) {
      $this->fetchConfirmedOrderQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->confirmedOrderModelFactoryLazyLoader->load() 
      );
    }
    return $this->fetchConfirmedOrderQuery;
  }

  public function getFetchConfirmedOrdersByTimeQuery(): FetchConfirmedOrdersByTimeQuery {
    if ($this->fetchConfirmedOrdersByTimeQuery === null) {
      $this->fetchConfirmedOrdersByTimeQuery = new FetchConfirmedOrdersByTimeQuery(
        $this->getFetchConfirmedOrderQuery(),
        $this->confirmedOrdersTableLazyLoader->load()
      ); 
    }
    return $this->fetchConfirmedOrdersByTimeQuery;
  }
  
  public function getInsertConfirmedOrderQuery(): InsertQuery<ConfirmedOrder> {
    if ($this->insertConfirmedOrderQuery === null) {
      $this->insertConfirmedOrderQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->confirmedOrdersTableLazyLoader->load(),
        $this->confirmedOrderModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load()
      ); 
    }
    return $this->insertConfirmedOrderQuery;
  }

  public function getConcreteInsertConfirmedOrderQuery(): InsertConfirmedOrderQuery {
    if ($this->concreteInsertConfirmedOrderQuery === null) {
      $this->concreteInsertConfirmedOrderQuery = new InsertConfirmedOrderQuery(
        $this->getInsertConfirmedOrderQuery(),
        $this->confirmedOrdersTableLazyLoader->load() 
      );
    }
    return $this->concreteInsertConfirmedOrderQuery;
  }

  /**
   * Reserved order policy queries
   */
  public function getFetchReservedOrderPolicyQuery(): FetchSingletonQuery<ReservedOrderPolicy> {
    if ($this->fetchSingletonRsvdOrderPolicyQuery === null) {
      $this->fetchSingletonRsvdOrderPolicyQuery = new FetchSingletonQuery(
        new FetchByIdQuery(
          new FetchByUniqueKeyQuery(
            new FetchQuery(
              $this->asyncMysqlConnectionLazyLoader->load(),
              $this->rsvdOrderPolicyModelFactoryLazyLoader->load()
            ),
            $this->rsvdOrderPolicyTableLazyLoader->load(),
            $this->constraintMapToConjunctiveWhereClauseTranslatorLazyLoader->load()
          ),
          $this->rsvdOrderPolicyTableLazyLoader->load() 
        )
      ); 
    }
    return $this->fetchSingletonRsvdOrderPolicyQuery;
  }
}
