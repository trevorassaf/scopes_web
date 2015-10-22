<?hh // strict

class QueryInjector {

  // Delete query
  private ?DeleteQuery $deleteQuery;
  private ?DeleteByIdQuery $deleteByIdQuery;

  // Update query
  private ?UpdateQuery $updateQuery;
  private ?UpdateByUniqueKeyQuery $updateByUniqueKeyQuery;
  private ?UpdateByIdQuery $updateByIdQuery;

  // User queries
  private ?InsertQuery<User> $insertUserQuery;
  private ?InsertUserQuery $concreteInsertUserQuery;
  private ?FetchQuery<User> $fetchUserQuery;
  private ?FetchByUniqueKeyQuery<User> $fetchUserByUniqueKeyQuery;
  private ?FetchByIdQuery<User> $fetchUserByIdQuery;

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
  private ?FetchByUniqueKeyQuery<RsvdOrder> $fetchRsvdOrderByUniqueKeyQuery;
  private ?FetchByIdQuery<RsvdOrder> $fetchRsvdOrderByIdQuery;
  private ?FetchReservedOrdersByTimeQuery $fetchRsvdOrdersByTimeQuery;
  private ?InsertQuery<RsvdOrder> $insertRsvdOrderQuery;
  private ?InsertReservedOrderQuery $concreteInsertRsvdOrderQuery;
  
  // Confirmed orders queries
  private ?FetchQuery<ConfirmedOrder> $fetchConfirmedOrderQuery;
  private ?FetchConfirmedOrdersByTimeQuery $fetchConfirmedOrdersByTimeQuery;
  private ?InsertQuery<ConfirmedOrder> $insertConfirmedOrderQuery;
  private ?InsertConfirmedOrderQuery $concreteInsertConfirmedOrderQuery;
  private ?FetchUsersConfirmedOrdersQuery $fetchUsersConfirmedOrdersQuery;
  private ?FetchConfirmedOrderCellLabelsQuery $fetchConfirmedOrderCellLabelsQuery;
  private ?FetchIsUserOwnedShortCodeQuery $fetchIsUserOwnedShortCodeQuery;
  private ?FetchUserShortCodesQuery $fetchUserShortCodesQuery;

  // Edited video order queries
  private ?InsertQuery<EditedVideoOrder> $insertEditedVideoOrderQuery;
  private ?InsertEditedVideoOrderQuery $concreteInsertEditedVideoOrderQuery;
  
  // Short codes
  private ?FetchQuery<ShortCode> $fetchShortCodesQuery;
  private ?FetchByUniqueKeyQuery<ShortCode> $fetchShortCodeByUniqueKeyQuery;
  private ?FetchByIdQuery<ShortCode> $fetchShortCodeByIdQuery;
  private ?InsertQuery<ShortCode> $insertShortCodeQuery;

  // Reserved order policy queries
  private ?FetchSingletonQuery<ReservedOrderPolicy> $fetchSingletonRsvdOrderPolicyQuery;
  private ?InsertQuery<ReservedOrderPolicy> $insertReservedOrderPolicyQuery;
  private ?InsertReservedOrderPolicyQuery $concreteInsertReservedOrderPolicyQuery;

  // Cell label queries
  private ?BatchInsertQuery<CellLabel> $batchInsertCellLabelQuery;
  private ?FetchQuery<CellLabel> $fetchCellLabelQuery;

  // Video packages
  private ?FetchQuery<BasicVideo> $fetchBasicVideosQuery;
  private ?FetchBasicVideosByOrderQuery $fetchBasicVideosByOrderQuery;
  private ?BatchInsertQuery<BasicVideo> $batchInsertBasicVideosQuery;
  private ?BatchInsertBasicVideosByOrderQuery $batchInsertBasicVideosByOrderQuery;

  private ?FetchQuery<CompositeVideo> $fetchCompositeVideosQuery;
  private ?FetchCompositeVideoByOrderQuery $fetchCompositeVideoByOrderQuery;
  private ?InsertQuery<CompositeVideo> $insertCompositeVideoQuery;
  private ?InsertCompositeVideoQuery $concreteInsertCompositeVideoQuery;

  private ?FetchQuery<CompletedBasicVideoSet> $fetchCompletedBasicVideoSetQuery;
  private ?FetchByUniqueKeyQuery<CompletedBasicVideoSet> $fetchCompletedBasicVideoSetByUniqueKeyQuery;
  private ?FetchCompletedBasicVideoSetByCompletedOrderQuery $fetchCompletedBasicVideoSetByCompletedOrderQuery;
  private ?InsertQuery<CompletedBasicVideoSet> $insertCompletedBasicVideoSetQuery;

  private ?FetchQuery<VideoUploadPolicy> $fetchVideoUploadPolicyQuery;
  private ?InsertQuery<VideoUploadPolicy> $insertVideoUploadPolicyQuery;
  private ?FetchQuery<VideoMimeType> $fetchVideoMimeTypesQuery;
  private ?InsertQuery<VideoMimeType> $insertVideoMimeTypeQuery;

  // Order Transactions
  private ?FetchQuery<ConfirmedOrderTransaction> $fetchConfirmedOrderTransactionQuery;
  private ?FetchConfirmedOrderTransactionQuery $concreteFetchConfirmedOrderTransactionQuery;
  private ?InsertQuery<ConfirmedOrderTransaction> $insertConfirmedOrderTransactionQuery;
  private ?FetchQuery<FailedConfirmedOrderTransaction> $fetchFailedConfirmedOrderTransactionQuery;
  private ?FetchFailedConfirmedOrderTransactionQuery $concreteFetchFailedConfirmedOrderTransactionQuery;
  private ?InsertQuery<FailedConfirmedOrderTransaction> $insertFailedConfirmedOrderTransactionQuery;
  private ?FetchQuery<OrderTransactionPolicy> $fetchOrderTransactionPolicyQuery;
  private ?FetchOrderTransactionPolicyQuery $concreteFetchOrderTransactionPolicyQuery;

  // Completed orders
  private ?FetchQuery<CompletedOrder> $fetchCompletedOrderQuery;
  private ?FetchByUniqueKeyQuery<CompletedOrder> $fetchCompletedOrderByUniqueKeyQuery;
  private ?FetchCompletedOrderByConfirmedOrderQuery $fetchCompletedOrderByConfirmedOrderQuery;
  private ?InsertQuery<CompletedOrder> $insertCompletedOrderQuery;



  public function __construct(
    private LazyLoader<AsyncMysqlConnection> $asyncMysqlConnectionLazyLoader,
    private LazyLoader<ConstraintMapToConjunctiveWhereClauseTranslator> $constraintMapToConjunctiveWhereClauseTranslatorLazyLoader,
    private LazyLoader<DateSerializer> $dateSerializerLazyLoader,
    private LazyLoader<TimeSerializer> $timeSerializerLazyLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLazyLoader,
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
    private LazyLoader<ConcreteModelFactory<ReservedOrderPolicy>> $rsvdOrderPolicyModelFactoryLazyLoader,
    private LazyLoader<CellLabelsTable> $cellLabelsTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<CellLabel>> $cellLabelModelFactoryLazyLoader,
    private LazyLoader<QueryExceptionFactory> $queryExceptionFactoryLazyLoader,
    private LazyLoader<ShortCodeTable> $shortCodeTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<ShortCode>> $shortCodeModelFactoryLazyLoader,
    private LazyLoader<EditedVideoOrderTable> $editedVideoOrderTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<EditedVideoOrder>> $editedVideoOrderModelFactoryLazyLoader,
    private LazyLoader<BasicVideosTable> $basicVideosTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<BasicVideo>> $basicVideoModelFactoryLazyLoader,
    private LazyLoader<CompositeVideoTable> $compositeVideoTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<CompositeVideo>> $compositeVideoModelFactoryLazyLoader,
    private LazyLoader<ConfirmedOrderTransactionTable> $confirmedOrderTransactionTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<ConfirmedOrderTransaction>> $confirmedOrderTransactionModelFactoryLazyLoader,
    private LazyLoader<FailedConfirmedOrderTransactionTable> $failedConfirmedOrderTransactionTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<FailedConfirmedOrderTransaction>> $failedConfirmedOrderTransactionModelFactoryLazyLoader,
    private LazyLoader<OrderTransactionPolicyTable> $orderTransactionPolicyTableLazyLoader,
    private LazyLoader<ModelFactory<OrderTransactionPolicy>> $orderTransactionPolicyModelFactoryLazyLoader,
    private LazyLoader<CompletedOrdersTable> $completedOrdersTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<CompletedOrder>> $completedOrderModelFactoryLazyLoader,
    private LazyLoader<CompletedBasicVideoSetTable> $completedBasicVideoSetTableLazyLoader,
    private LazyLoader<ConcreteModelFactory<CompletedBasicVideoSet>> $completedBasicVideoSetModelFactoryLazyLoader,
    private LazyLoader<VideoUploadPolicyTable> $videoUploadPolicyTableLazyLoader,
    private LazyLoader<ModelFactory<VideoUploadPolicy>> $videoUploadPolicyModelFactoryLazyLoader,
    private LazyLoader<VideoMimeTypesTable> $videoMimeTypesTable,
    private LazyLoader<ConcreteModelFactory<VideoMimeType>> $videoMimeTypeModelFactoryLazyLoader
  ) {}

  public function getUpdateQuery(): UpdateQuery {
    if ($this->updateQuery === null) {
      $this->updateQuery = new UpdateQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      );
    }
    return $this->updateQuery;
  }

  public function getUpdateByUniqueKeyQuery(): UpdateByUniqueKeyQuery {
    if ($this->updateByUniqueKeyQuery === null) {
      $this->updateByUniqueKeyQuery = new UpdateByUniqueKeyQuery(
        $this->getUpdateQuery(),
        $this->constraintMapToConjunctiveWhereClauseTranslatorLazyLoader->load() 
      );
    }
    return $this->updateByUniqueKeyQuery;
  }

  public function getUpdateByIdQuery(): UpdateByIdQuery {
    if ($this->updateByIdQuery === null) {
      $this->updateByIdQuery = new UpdateByIdQuery(
        $this->getUpdateByUniqueKeyQuery()
      ); 
    }
    return $this->updateByIdQuery;
  }

  /**
   * User queries
   */
  public function getInsertUserQuery(): InsertQuery<User> {
    if ($this->insertUserQuery === null) {
      $this->insertUserQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->usersTableLazyLoader->load(),
        $this->userModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      );
    }  
    return $this->insertUserQuery;
  }

  public function getConcreteInsertUserQuery(): InsertUserQuery {
    if ($this->concreteInsertUserQuery === null) {
      $this->concreteInsertUserQuery = new InsertUserQuery(
        $this->getInsertUserQuery(),
        $this->usersTableLazyLoader->load(),
        $this->timestampSerializerLazyLoader->load()
      );
    }
    return $this->concreteInsertUserQuery;
  }

  public function getFetchUserQuery(): FetchQuery<User> {
    if ($this->fetchUserQuery === null) {
      $this->fetchUserQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->userModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
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

  public function getFetchUserByIdQuery(): FetchByIdQuery<User> {
    if ($this->fetchUserByIdQuery === null) {
      $this->fetchUserByIdQuery = new FetchByIdQuery(
        $this->getFetchUserByUniqueKeyQuery(),
        $this->usersTableLazyLoader->load() 
      );
    }
   return $this->fetchUserByIdQuery; 
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
        $this->insertQueryCreaterLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
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
        $this->regularWeekDayModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
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
        $this->insertQueryCreaterLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      );
    }
    return $this->insertRegularTimeQuery;
  }

  public function getConcreteInsertRegularTimeQuery(): InsertRegularTimeQuery {
    if ($this->concreteInsertRegularTimeQuery === null) {
      $this->concreteInsertRegularTimeQuery = new InsertRegularTimeQuery(
        $this->getInsertRegularTimeQuery(),
        $this->regularTimesTableLazyLoader->load(),
        $this->timeSerializerLazyLoader->load()
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
        $this->regularTimeModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
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
        $this->insertQueryCreaterLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
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
        $this->regularEdgeModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
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
        $this->irregularDateModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
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
        $this->insertQueryCreaterLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      ); 
    }
    return $this->insertIrregularDateQuery;
  }
  
  public function getConcreteInsertIrregularDateQuery(): InsertIrregularDateQuery {
    if ($this->concreteInsertIrregularDateQuery === null) {
      $this->concreteInsertIrregularDateQuery = new InsertIrregularDateQuery(
        $this->getInsertIrregularDateQuery(),
        $this->irregularDatesTableLazyLoader->load(),
        $this->dateSerializerLazyLoader->load()
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
        $this->irregularTimeModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
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
        $this->insertQueryCreaterLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      ); 
    }
    return $this->insertIrregularTimeQuery;
  }

  public function getConcreteInsertIrregularTimeQuery(): InsertIrregularTimeQuery {
    if ($this->concreteInsertIrregularTimeQuery === null) {
      $this->concreteInsertIrregularTimeQuery = new InsertIrregularTimeQuery(
        $this->getInsertIrregularTimeQuery(),
        $this->irregularTimesTableLazyLoader->load(),
        $this->timeSerializerLazyLoader->load()
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
        $this->rsvdOrderModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      );
    }
    return $this->fetchRsvdOrderQuery;
  }

  public function getFetchRsvdOrdersByTimeQuery(): FetchReservedOrdersByTimeQuery {
    if ($this->fetchRsvdOrdersByTimeQuery === null) {
      $this->fetchRsvdOrdersByTimeQuery = new FetchReservedOrdersByTimeQuery(
        $this->getFetchRsvdOrderQuery(), 
        $this->rsvdOrdersTableLazyLoader->load(),
        $this->timestampSerializerLazyLoader->load()
      );
    }
    return $this->fetchRsvdOrdersByTimeQuery;
  }

  public function getFetchRsvdOrderByUniqueKeyQuery(): FetchByUniqueKeyQuery<RsvdOrder> {
    if ($this->fetchRsvdOrderByUniqueKeyQuery === null) {
      $this->fetchRsvdOrderByUniqueKeyQuery = new FetchByUniqueKeyQuery(
        $this->getFetchRsvdOrderQuery(),
        $this->rsvdOrdersTableLazyLoader->load(),
        $this->constraintMapToConjunctiveWhereClauseTranslatorLazyLoader->load() 
      );
    }
    return $this->fetchRsvdOrderByUniqueKeyQuery;
  }

  public function getFetchRsvdOrderByIdQuery(): FetchByIdQuery<RsvdOrder> {
    if ($this->fetchRsvdOrderByIdQuery === null) {
      $this->fetchRsvdOrderByIdQuery = new FetchByIdQuery(
        $this->getFetchRsvdOrderByUniqueKeyQuery(),
        $this->rsvdOrdersTableLazyLoader->load() 
      ); 
    }
    return $this->fetchRsvdOrderByIdQuery;
  }

  public function getInsertRsvdOrderQuery(): InsertQuery<RsvdOrder> {
    if ($this->insertRsvdOrderQuery === null) {
      $this->insertRsvdOrderQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->rsvdOrdersTableLazyLoader->load(),
        $this->rsvdOrderModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      ); 
    }
    return $this->insertRsvdOrderQuery;
  }

  public function getConcreteInsertRsvdOrderQuery(): InsertReservedOrderQuery {
    if ($this->concreteInsertRsvdOrderQuery === null) {
      $this->concreteInsertRsvdOrderQuery = new InsertReservedOrderQuery(
        $this->getInsertRsvdOrderQuery(),
        $this->rsvdOrdersTableLazyLoader->load(),
        $this->timestampSerializerLazyLoader->load()
      );
    }
    return $this->concreteInsertRsvdOrderQuery;
  }

  public function getDeleteQuery(): DeleteQuery {
    if ($this->deleteQuery === null) {
      $this->deleteQuery = new DeleteQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      ); 
    } 
    return $this->deleteQuery;
  }

  public function getDeleteByIdQuery(): DeleteByIdQuery {
    if ($this->deleteByIdQuery === null) {
      $this->deleteByIdQuery = new DeleteByIdQuery(
        $this->getDeleteQuery()
      ); 
    }
   return $this->deleteByIdQuery; 
  }

  /**
   * Confirmed order queries
   */
  public function getFetchConfirmedOrderQuery(): FetchQuery<ConfirmedOrder> {
    if ($this->fetchConfirmedOrderQuery === null) {
      $this->fetchConfirmedOrderQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->confirmedOrderModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      );
    }
    return $this->fetchConfirmedOrderQuery;
  }

  public function getFetchConfirmedOrdersByTimeQuery(): FetchConfirmedOrdersByTimeQuery {
    if ($this->fetchConfirmedOrdersByTimeQuery === null) {
      $this->fetchConfirmedOrdersByTimeQuery = new FetchConfirmedOrdersByTimeQuery(
        $this->getFetchConfirmedOrderQuery(),
        $this->confirmedOrdersTableLazyLoader->load(),
        $this->timestampSerializerLazyLoader->load()
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
        $this->insertQueryCreaterLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      ); 
    }
    return $this->insertConfirmedOrderQuery;
  }

  public function getConcreteInsertConfirmedOrderQuery(): InsertConfirmedOrderQuery {
    if ($this->concreteInsertConfirmedOrderQuery === null) {
      $this->concreteInsertConfirmedOrderQuery = new InsertConfirmedOrderQuery(
        $this->getInsertConfirmedOrderQuery(),
        $this->confirmedOrdersTableLazyLoader->load(),
        $this->timestampSerializerLazyLoader->load()
      );
    }
    return $this->concreteInsertConfirmedOrderQuery;
  }

  public function getFetchUsersConfirmedOrdersQuery(): FetchUsersConfirmedOrdersQuery {
    if ($this->fetchUsersConfirmedOrdersQuery === null) {
      $this->fetchUsersConfirmedOrdersQuery = new FetchUsersConfirmedOrdersQuery(
        $this->getFetchConfirmedOrderQuery(),
        $this->confirmedOrdersTableLazyLoader->load() 
      ); 
    }
    return $this->fetchUsersConfirmedOrdersQuery;
  }

  public function getFetchConfirmedOrderCellLabelsQuery(): FetchConfirmedOrderCellLabelsQuery {
    if ($this->fetchConfirmedOrderCellLabelsQuery === null) {
      $this->fetchConfirmedOrderCellLabelsQuery = new FetchConfirmedOrderCellLabelsQuery(
        $this->getFetchCellLabelQuery(),
        $this->cellLabelsTableLazyLoader->load() 
      ); 
    }
    return $this->fetchConfirmedOrderCellLabelsQuery;
  }

  public function getInsertEditedVideoOrderQuery(): InsertQuery<EditedVideoOrder> {
    if ($this->insertEditedVideoOrderQuery === null) {
      $this->insertEditedVideoOrderQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->editedVideoOrderTableLazyLoader->load(),
        $this->editedVideoOrderModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      ); 
    }
    return $this->insertEditedVideoOrderQuery;
  }

  public function getConcreteInsertEditedVideoOrderQuery(): InsertEditedVideoOrderQuery {
    if ($this->concreteInsertEditedVideoOrderQuery === null) {
      $this->concreteInsertEditedVideoOrderQuery = new InsertEditedVideoOrderQuery(
        $this->getInsertEditedVideoOrderQuery(),
        $this->editedVideoOrderTableLazyLoader->load()
      ); 
    }
    return $this->concreteInsertEditedVideoOrderQuery;
  }

  public function getFetchShortCodesQuery(): FetchQuery<ShortCode> {
    if ($this->fetchShortCodesQuery === null) {
      $this->fetchShortCodesQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->shortCodeModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      );
    }
    return $this->fetchShortCodesQuery;
  }

  public function getFetchShortCodeByUniqueKeyQuery(): FetchByUniqueKeyQuery<ShortCode> {
    if ($this->fetchShortCodeByUniqueKeyQuery === null) {
      $this->fetchShortCodeByUniqueKeyQuery = new FetchByUniqueKeyQuery(
        $this->getFetchShortCodesQuery(),
        $this->shortCodeTableLazyLoader->load(),
        $this->constraintMapToConjunctiveWhereClauseTranslatorLazyLoader->load()
      );
    }
    return $this->fetchShortCodeByUniqueKeyQuery;
  }

  public function getFetchShortCodeByIdQuery(): FetchByIdQuery<ShortCode> {
    if ($this->fetchShortCodeByIdQuery === null) {
      $this->fetchShortCodeByIdQuery = new FetchByIdQuery(
        $this->getFetchShortCodeByUniqueKeyQuery(),
        $this->shortCodeTableLazyLoader->load() 
      );
    }
    return $this->fetchShortCodeByIdQuery;
  }

  public function getInsertShortCodeQuery(): InsertQuery<ShortCode> {
    if ($this->insertShortCodeQuery === null) {
      $this->insertShortCodeQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->shortCodeTableLazyLoader->load(),
        $this->shortCodeModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      ); 
    }
   return $this->insertShortCodeQuery; 
  }

  public function getFetchUserShortCodesQuery(): FetchUserShortCodesQuery {
    if ($this->fetchUserShortCodesQuery === null) {
      $this->fetchUserShortCodesQuery = new FetchUserShortCodesQuery(
        $this->getFetchShortCodesQuery(),
        $this->shortCodeTableLazyLoader->load()
      );
    }
    return $this->fetchUserShortCodesQuery;
  }

  public function getFetchIsUserOwnedShortCodeQuery(): FetchIsUserOwnedShortCodeQuery {
    if ($this->fetchIsUserOwnedShortCodeQuery === null) {
      $this->fetchIsUserOwnedShortCodeQuery = new FetchIsUserOwnedShortCodeQuery(
        $this->getFetchUserShortCodesQuery()
      ); 
    }
    return $this->fetchIsUserOwnedShortCodeQuery;
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
              $this->rsvdOrderPolicyModelFactoryLazyLoader->load(),
              $this->queryExceptionFactoryLazyLoader->load()
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

  public function getInsertReservedOrderPolicyQuery(): InsertQuery<ReservedOrderPolicy> {
    if ($this->insertReservedOrderPolicyQuery === null) {
      $this->insertReservedOrderPolicyQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->rsvdOrderPolicyTableLazyLoader->load(),
        $this->rsvdOrderPolicyModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      ); 
    }
    return $this->insertReservedOrderPolicyQuery;
  }

  public function getConcreteInsertReservedOrderPolicyQuery(): InsertReservedOrderPolicyQuery {
    if ($this->concreteInsertReservedOrderPolicyQuery === null) {
      $this->concreteInsertReservedOrderPolicyQuery = new InsertReservedOrderPolicyQuery(
        $this->getInsertReservedOrderPolicyQuery(),
        $this->rsvdOrderPolicyTableLazyLoader->load()
      ); 
    }
    return $this->concreteInsertReservedOrderPolicyQuery;
  }

  /**
   * Cell label queries
   */
  public function getBatchInsertCellLabelsQuery(): BatchInsertQuery<CellLabel> {
    if ($this->batchInsertCellLabelQuery === null) {
      $this->batchInsertCellLabelQuery = new BatchInsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->cellLabelsTableLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load()
      ); 
    } 
    return $this->batchInsertCellLabelQuery;
  }

  public function getFetchCellLabelQuery(): FetchQuery<CellLabel> {
    if ($this->fetchCellLabelQuery === null) {
      $this->fetchCellLabelQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->cellLabelModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load() 
      ); 
    }
    return $this->fetchCellLabelQuery;
  }

  /**
   * Video queries
   */
  public function getFetchBasicVideosQuery(): FetchQuery<BasicVideo> {
    if ($this->fetchBasicVideosQuery === null) {
      $this->fetchBasicVideosQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->basicVideoModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load() 
      ); 
    }
    return $this->fetchBasicVideosQuery;
  }

  public function getFetchBasicVideosByOrderQuery(): FetchBasicVideosByOrderQuery {
    if ($this->fetchBasicVideosByOrderQuery === null) {
      $this->fetchBasicVideosByOrderQuery = new FetchBasicVideosByOrderQuery(
        $this->getFetchBasicVideosQuery(),
        $this->basicVideosTableLazyLoader->load() 
      ); 
    }
    return $this->fetchBasicVideosByOrderQuery;
  }

  protected function getBatchInsertBasicVideosQuery(): BatchInsertQuery<BasicVideo> {
    if ($this->batchInsertBasicVideosQuery === null) {
      $this->batchInsertBasicVideosQuery = new BatchInsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->basicVideosTableLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load()
      ); 
    }
    return $this->batchInsertBasicVideosQuery;
  }
  
  public function getBatchInsertBasicVideosByOrderQuery(): BatchInsertBasicVideosByOrderQuery {
    if ($this->batchInsertBasicVideosByOrderQuery === null) {
        $this->batchInsertBasicVideosByOrderQuery = new BatchInsertBasicVideosByOrderQuery(
        $this->getBatchInsertBasicVideosQuery(),
        $this->basicVideosTableLazyLoader->load()
      ); 
    }
    return $this->batchInsertBasicVideosByOrderQuery;
  }

  public function getFetchCompositeVideosQuery(): FetchQuery<CompositeVideo> {
    if ($this->fetchCompositeVideosQuery === null) {
      $this->fetchCompositeVideosQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->compositeVideoModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load() 
      ); 
    }
    return $this->fetchCompositeVideosQuery;
  }
  
  public function getFetchCompositeVideoByOrderQuery(): FetchCompositeVideoByOrderQuery {
    if ($this->fetchCompositeVideoByOrderQuery === null) {
      $this->fetchCompositeVideoByOrderQuery = new FetchCompositeVideoByOrderQuery(
        $this->getFetchCompositeVideosQuery(),
        $this->compositeVideoTableLazyLoader->load() 
      ); 
    }
    return $this->fetchCompositeVideoByOrderQuery;
  }

  public function getInsertCompositeVideoQuery(): InsertQuery<CompositeVideo> {
    if ($this->insertCompositeVideoQuery === null) {
      $this->insertCompositeVideoQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->compositeVideoTableLazyLoader->load(),
        $this->compositeVideoModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
         
      ); 
    }
    return $this->insertCompositeVideoQuery;
  }

  public function getConcreteInsertCompositeVideoQuery(): InsertCompositeVideoQuery {
    if ($this->concreteInsertCompositeVideoQuery === null) {
      $this->concreteInsertCompositeVideoQuery = new InsertCompositeVideoQuery(
        $this->getInsertCompositeVideoQuery(),
        $this->compositeVideoTableLazyLoader->load(),
        $this->timestampSerializerLazyLoader->load()
      ); 
    }    
    return $this->concreteInsertCompositeVideoQuery;
  }

  /**
   * Order Transactions
   */
  public function getFetchConfirmedOrderTransactionQuery(): FetchQuery<ConfirmedOrderTransaction> {
    if ($this->fetchConfirmedOrderTransactionQuery === null) {
      $this->fetchConfirmedOrderTransactionQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->confirmedOrderTransactionModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      ); 
    }
    return $this->fetchConfirmedOrderTransactionQuery;
  }

  public function getConcreteFetchConfirmedOrderTransactionQuery(): FetchConfirmedOrderTransactionQuery {
    if ($this->concreteFetchConfirmedOrderTransactionQuery === null) {
      $this->concreteFetchConfirmedOrderTransactionQuery = new FetchConfirmedOrderTransactionQuery(
        $this->getFetchConfirmedOrderTransactionQuery(),
        $this->confirmedOrderTransactionTableLazyLoader->load()
      ); 
    }
    return $this->concreteFetchConfirmedOrderTransactionQuery; 
  }

  public function getInsertConfirmedOrderTransactionQuery(): InsertQuery<ConfirmedOrderTransaction> {
    if ($this->insertConfirmedOrderTransactionQuery === null) {
      $this->insertConfirmedOrderTransactionQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->confirmedOrderTransactionTableLazyLoader->load(),
        $this->confirmedOrderTransactionModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      );
    }
    return $this->insertConfirmedOrderTransactionQuery;
  }

  public function getFetchFailedConfirmedOrderTransactionQuery(): FetchQuery<FailedConfirmedOrderTransaction> {
    if ($this->fetchFailedConfirmedOrderTransactionQuery === null) {
      $this->fetchFailedConfirmedOrderTransactionQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->failedConfirmedOrderTransactionModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      ); 
    }
    return $this->fetchFailedConfirmedOrderTransactionQuery;
  }

  public function getConcreteFetchFailedConfirmedOrderTransactionQuery(): FetchFailedConfirmedOrderTransactionQuery {
    if ($this->concreteFetchFailedConfirmedOrderTransactionQuery === null) {
      $this->concreteFetchFailedConfirmedOrderTransactionQuery = new FetchFailedConfirmedOrderTransactionQuery(
        $this->getFetchFailedConfirmedOrderTransactionQuery(),
        $this->failedConfirmedOrderTransactionTableLazyLoader->load()
      ); 
    }
    return $this->concreteFetchFailedConfirmedOrderTransactionQuery; 
  }
  
  public function getInsertFailedConfirmedOrderTransactionQuery(): InsertQuery<FailedConfirmedOrderTransaction> {
    if ($this->insertFailedConfirmedOrderTransactionQuery === null) {
      $this->insertFailedConfirmedOrderTransactionQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->failedConfirmedOrderTransactionTableLazyLoader->load(),
        $this->failedConfirmedOrderTransactionModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      );
    }
    return $this->insertFailedConfirmedOrderTransactionQuery;
  }

  public function getFetchOrderTransactionPolicyQuery(): FetchQuery<OrderTransactionPolicy> {
    if ($this->fetchOrderTransactionPolicyQuery === null) {
      $this->fetchOrderTransactionPolicyQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->orderTransactionPolicyModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      ); 
    }
    return $this->fetchOrderTransactionPolicyQuery;
  }

  public function getConcreteFetchOrderTransactionPolicyQuery(): FetchOrderTransactionPolicyQuery {
    if ($this->concreteFetchOrderTransactionPolicyQuery === null) {
      $this->concreteFetchOrderTransactionPolicyQuery = new FetchOrderTransactionPolicyQuery(
        $this->getFetchOrderTransactionPolicyQuery(),
        $this->orderTransactionPolicyTableLazyLoader->load(),
        $this->timestampSerializerLazyLoader->load() 
      ); 
    }
    return $this->concreteFetchOrderTransactionPolicyQuery;
  }

  /**
   * Completed order queries
   */
  public function getFetchCompletedOrderQuery(): FetchQuery<CompletedOrder> {
    if ($this->fetchCompletedOrderQuery === null) {
      $this->fetchCompletedOrderQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->completedOrderModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      ); 
    }
    return $this->fetchCompletedOrderQuery;
  }

  public function getFetchCompletedOrderByUniqueKeyQuery(): FetchByUniqueKeyQuery<CompletedOrder> {
    if ($this->fetchCompletedOrderByUniqueKeyQuery === null) {
      $this->fetchCompletedOrderByUniqueKeyQuery = new FetchByUniqueKeyQuery(
        $this->getFetchCompletedOrderQuery(),
        $this->completedOrdersTableLazyLoader->load(),
        $this->constraintMapToConjunctiveWhereClauseTranslatorLazyLoader->load()
      ); 
    }
    return $this->fetchCompletedOrderByUniqueKeyQuery;
  }

  public function getFetchCompletedOrderByConfirmedOrderQuery(): FetchCompletedOrderByConfirmedOrderQuery {
    if ($this->fetchCompletedOrderByConfirmedOrderQuery === null) {
      $this->fetchCompletedOrderByConfirmedOrderQuery = new FetchCompletedOrderByConfirmedOrderQuery(
        $this->getFetchCompletedOrderByUniqueKeyQuery(),
        $this->completedOrdersTableLazyLoader->load() 
      ); 
    }
    return $this->fetchCompletedOrderByConfirmedOrderQuery;
  }

  public function getInsertCompletedOrderQuery(): InsertQuery<CompletedOrder> {
    if ($this->insertCompletedOrderQuery === null) {
      $this->insertCompletedOrderQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->completedOrdersTableLazyLoader->load(),
        $this->completedOrderModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      ); 
    }
    return $this->insertCompletedOrderQuery;
  }

  /**
   * Completed video packages
   */
  public function getFetchCompletedBasicVideoSetQuery(): FetchQuery<CompletedBasicVideoSet> {
    if ($this->fetchCompletedBasicVideoSetQuery === null) {
      $this->fetchCompletedBasicVideoSetQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->completedBasicVideoSetModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      );
    }
    return $this->fetchCompletedBasicVideoSetQuery;
  }

  public function getInsertCompletedBasicVideoSetQuery(): InsertQuery<CompletedBasicVideoSet> {
    if ($this->insertCompletedBasicVideoSetQuery === null) {
      $this->insertCompletedBasicVideoSetQuery = new InsertQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->completedBasicVideoSetTableLazyLoader->load(),
        $this->completedBasicVideoSetModelFactoryLazyLoader->load(),
        $this->insertQueryCreaterLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      ); 
    }
    return $this->insertCompletedBasicVideoSetQuery;
  }

  public function getFetchCompletedBasicVideoSetByUniqueKeyQuery(): FetchByUniqueKeyQuery<CompletedBasicVideoSet> {
    if ($this->fetchCompletedBasicVideoSetByUniqueKeyQuery === null) {
      $this->fetchCompletedBasicVideoSetByUniqueKeyQuery = new FetchByUniqueKeyQuery(
        $this->getFetchCompletedBasicVideoSetQuery(),
        $this->completedBasicVideoSetTableLazyLoader->load(),
        $this->constraintMapToConjunctiveWhereClauseTranslatorLazyLoader->load() 
      ); 
    }
    return $this->fetchCompletedBasicVideoSetByUniqueKeyQuery;
  }

  public function getFetchCompletedBasicVideoSetByCompletedOrderQuery(): FetchCompletedBasicVideoSetByCompletedOrderQuery {
    if ($this->fetchCompletedBasicVideoSetByCompletedOrderQuery === null) {
      $this->fetchCompletedBasicVideoSetByCompletedOrderQuery = new FetchCompletedBasicVideoSetByCompletedOrderQuery(
        $this->getFetchCompletedBasicVideoSetByUniqueKeyQuery(),
        $this->completedBasicVideoSetTableLazyLoader->load()
      ); 
    }
    return $this->fetchCompletedBasicVideoSetByCompletedOrderQuery;
  }
  
  public function getFetchVideoUploadPolicyQuery(): FetchQuery<VideoUploadPolicy> {
    if ($this->fetchVideoUploadPolicyQuery === null) {
      $this->fetchVideoUploadPolicyQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->videoUploadPolicyModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      ); 
    }
    return $this->fetchVideoUploadPolicyQuery;
  }

  public function getFetchVideoMimeTypesQuery(): FetchQuery<VideoMimeType> {
    if ($this->fetchVideoMimeTypesQuery === null) {
      $this->fetchVideoMimeTypesQuery = new FetchQuery(
        $this->asyncMysqlConnectionLazyLoader->load(),
        $this->videoMimeTypeModelFactoryLazyLoader->load(),
        $this->queryExceptionFactoryLazyLoader->load()
      ); 
    }
    return $this->fetchVideoUploadPolicyQuery;
  }
}
