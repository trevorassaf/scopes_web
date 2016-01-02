<?hh // strict

class MethodInjector {

  // User methods
  private ?CreateUserMethod $createUserMethod;
  private ?GetUserByEmailMethod $getUserByEmailMethod;
  private ?GetAllUsersMethod $getAllUsersMethod;
  private ?AssignUserPrivilegesMethod $assignUserPrivilegesMethod;
  private ?CreateUserPrivilegesMethod $createUserPrivilegesMethod;
  private ?CheckUserPrivilegeMethod $checkUserPrivilegeMethod;

  // User agent methods
  private ?GetUserAgentMethod $getUserAgentMethod;

  // Regular week day methods
  private ?CreateRegularWeekDayMethod $createRegularWeekDayMethod;

  // Regular time methods
  private ?CreateRegularTimeMethod $createRegularTimeMethod;

  // Regular edge methods
  private ?CreateRegularWeekDayRegularTimeEdgeMethod $createRegularEdgeMethod;

  // Irregular date methods
  private ?CreateIrregularDateMethod $createIrregularDateMethod;

  // Irregular time methods
  private ?CreateIrregularTimeMethod $createIrregularTimeMethod;

  // Is conflicting reserved order method
  private ?IsConflictingReservedOrderMethod $isConflictingReservedOrderMethod;

  // Is valid reserved order method
  private ?IsValidReservedOrderMethod $isValidReservedOrderMethod;

  // Reserve order method
  private ?ReserveOrderMethod $reserveOrderMethod;
  private ?DeleteReservedOrderMethod $deleteReservedOrderMethod;
  private ?GetUsersReservedOrdersMethod $getUsersReservedOrdersMethod;

  // Confirm order method
  private ?ConfirmOrderMethod $confirmOrderMethod;
  private ?UpdateConfirmedOrderMethod $updateConfirmedOrderMethod;
  private ?DeleteConfirmedOrderMethod $deleteConfirmedOrderMethod;
  private ?GetUsersConfirmedOrdersAndCellLabelsMethod $getUsersConfirmedOrdersAndCellLabelsMethod;
  private ?GetUsersConfirmedOrdersMethod $getUsersConfirmedOrdersMethod;

  // Cell label methods
  private ?UpdateCellLabelMethod $updateCellLabelMethod;
  private ?DeleteCellLabelMethod $deleteCellLabelMethod;

  // Policy methods
  private ?CreateReservedOrderPolicyMethod $createReservedOrderPolicyMethod;
  private ?MakeVideoUploadPolicyMethod $makeVideoUploadPolicyMethod;

  // Transaction methods
  private ?ExecuteTransactionsForTimeIntervalMethod $executeTransactionsForTimeIntervalMethod;
  private ?ExecuteOrderTransactionMethod $executeOrderTransactionMethod;

  // Video methods
  private ?UploadBasicVideoMethod $uploadBasicVideoMethod;
  private ?BasicVideoPathFormatMethod $basicVideoPathFormatMethod;
  private ?UploadEditedVideoMethod $uploadEditedVideoMethod;
  private ?CreateVideoMimeTypeMethod $createVideoMimeTypeMethod;

  // Short code methods
  private ?CreateShortCodeMethod $createShortCodeMethod;

  // Complete order methods
  private ?CompleteOrderMethod $completeOrderMethod;
  private ?GetUsersCompletedOrdersMethod $getUsersCompletedOrdersMethod;

  public function __construct(
    private QueryInjector $queryInjector,
    private LazyLoader<UsersTable> $usersTableLoader,
    private LazyLoader<RegularWeekDaysTable> $regularWeekDaysTableLoader,
    private LazyLoader<RegularTimesTable> $regularTimesTableLoader,
    private LazyLoader<RegularWeekDayRegularTimeEdgesTable> $regularEdgesTableLoader,
    private LazyLoader<IrregularDatesTable> $irregularDatesTableLoader,
    private LazyLoader<IrregularTimesTable> $irregularTimesTableLoader,
    private LazyLoader<CellLabelsTable> $cellsLabelTableLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLoader,
    private LazyLoader<HRTimeSerializer> $timeSerializerLoader,
    private LazyLoader<DateSerializer> $dateSerializerLoader,
    private LazyLoader<TimestampBuilder> $timestampBuilderLoader,
    private LazyLoader<DateToDayOfTheWeekConverter> $dateToDayOfTheWeekConverterLoader,
    private LazyLoader<TimestampSegmentExpander> $timestampSegmentExpanderLoader,
    private LazyLoader<ConfirmedOrdersTable> $confirmedOrdersTableLoader,
    private LazyLoader<RsvdOrdersTable> $rsvdOrdersTableLoader,
    private Logger $logger,
    private LazyLoader<TimestampSegmentFactory> $timestampSegmentFactoryLoader,
    private LazyLoader<ConfirmedOrderTransactionTable> $confirmedOrderTransactionTableLoader,
    private LazyLoader<FailedConfirmedOrderTransactionTable> $failedConfirmedOrderTransactionTableLoader,
    private HttpUploadedFilesFetcher $httpUploadedFilesFetcher,
    private VideoMimeTypesTable $videoMimeTypesTable
  ) {}

  public function getCreateUserMethod(): CreateUserMethod {
    if ($this->createUserMethod === null) {
      $this->createUserMethod = new CreateUserMethod(
        $this->queryInjector->getConcreteInsertUserQuery(),
        $this->usersTableLoader->load(),
        $this->timestampBuilderLoader->load()
      );
    }       
    return $this->createUserMethod;
  }

  public function getGetUserByEmailMethod(): GetUserByEmailMethod {
    if ($this->getUserByEmailMethod === null) {
      $this->getUserByEmailMethod = new GetUserByEmailMethod(
        $this->queryInjector->getFetchUserByUniqueKeyQuery(),
        $this->usersTableLoader->load() 
      ); 
    }
    return $this->getUserByEmailMethod; 
  }

  public function getGetAllUsersMethod(): GetAllUsersMethod {
    if ($this->getAllUsersMethod === null) {
      $this->getAllUsersMethod = new GetAllUsersMethod(
        $this->queryInjector->getFetchUserQuery(),
        $this->usersTableLoader->load() 
      ); 
    }
    return $this->getAllUsersMethod;
  }

  /**
   * Regular week day methods 
   */
  public function getCreateRegularWeekDayMethod(): CreateRegularWeekDayMethod {
    if ($this->createRegularWeekDayMethod === null) {
      $this->createRegularWeekDayMethod = new CreateRegularWeekDayMethod(
        $this->queryInjector->getConcreteInsertRegularWeekDayQuery(),
        $this->queryInjector->getFetchRegularWeekDayByIdQuery(),
        $this->regularWeekDaysTableLoader->load() 
      );
    }
    return $this->createRegularWeekDayMethod;
  }

  /**
   * Regular time methods
   */
  public function getCreateRegularTimeMethod(): CreateRegularTimeMethod {
    if ($this->createRegularTimeMethod === null) {
      $this->createRegularTimeMethod = new CreateRegularTimeMethod(
        $this->queryInjector->getConcreteInsertRegularTimeQuery(),
        $this->queryInjector->getFetchRegularTimeByUniqueKeyQuery(),
        $this->regularTimesTableLoader->load(),
        $this->timeSerializerLoader->load()
      );
    }
    return $this->createRegularTimeMethod;
  }

  /**
   * Regular edge methods
   */
  public function getCreateRegularEdgeMethod(): CreateRegularWeekDayRegularTimeEdgeMethod {
    if ($this->createRegularEdgeMethod === null) {
      $this->createRegularEdgeMethod = new CreateRegularWeekDayRegularTimeEdgeMethod(
        $this->queryInjector->getConcreteInsertRegularEdgeQuery(),
        $this->queryInjector->getFetchRegularEdgeByUniqueKeyQuery(),
        $this->regularEdgesTableLoader->load() 
      );
    } 
    return $this->createRegularEdgeMethod;
  }

  /**
   * Irregular date methods
   */
  public function getCreateIrregularDateMethod(): CreateIrregularDateMethod {
    if ($this->createIrregularDateMethod === null) {
      $this->createIrregularDateMethod = new CreateIrregularDateMethod(
        $this->queryInjector->getConcreteInsertIrregularDateQuery(),
        $this->queryInjector->getFetchIrregularDateByUniqueKeyQuery(),
        $this->irregularDatesTableLoader->load(),
        $this->dateSerializerLoader->load()
      );
    }   
    return $this->createIrregularDateMethod;
  }

  /**
   * Irregular time methods
   */
  public function getCreateIrregularTimeMethod(): CreateIrregularTimeMethod {
    if ($this->createIrregularTimeMethod === null) {
      $this->createIrregularTimeMethod = new CreateIrregularTimeMethod(
        $this->queryInjector->getConcreteInsertIrregularTimeQuery(),
        $this->irregularTimesTableLoader->load() 
      );
    }   
    return $this->createIrregularTimeMethod;
  }

  /**
   * Is conflicting reserved order method
   */
  public function getIsConflictingReservedOrderMethod(): IsConflictingReservedOrderMethod {
    if ($this->isConflictingReservedOrderMethod === null) {
      $this->isConflictingReservedOrderMethod = new IsConflictingReservedOrderMethod(
        $this->queryInjector->getFetchRsvdOrdersByTimeQuery(),
        $this->queryInjector->getFetchConfirmedOrdersByTimeQuery(),
        $this->queryInjector->getFetchReservedOrderPolicyQuery(),
        $this->logger,
        $this->timestampSegmentFactoryLoader->load()
      ); 
    } 
    return $this->isConflictingReservedOrderMethod;
  }

  /**
   * Is valid reserved order method
   */
  public function getIsValidReservedOrderMethod(): IsValidReservedOrderMethod {
    if ($this->isValidReservedOrderMethod === null) {
      $this->isValidReservedOrderMethod = new IsValidReservedOrderMethod(
        $this->queryInjector->getFetchRegularEdgeQuery(),
        $this->regularEdgesTableLoader->load(),
        $this->queryInjector->getFetchRegularTimeQuery(),
        $this->regularTimesTableLoader->load(),
        $this->queryInjector->getConcreteFetchIrregularTimeQuery(),
        $this->queryInjector->getFetchIrregularDateByUniqueKeyQuery(),
        $this->irregularDatesTableLoader->load(),
        $this->dateSerializerLoader->load(),
        $this->dateToDayOfTheWeekConverterLoader->load(),
        $this->timestampSegmentExpanderLoader->load()
      ); 
    }
    return $this->isValidReservedOrderMethod;
  }

  /**
   * Reserve order methods
   */
  public function getReserveOrderMethod(): ReserveOrderMethod {
    if ($this->reserveOrderMethod === null) {
      $this->reserveOrderMethod = new ReserveOrderMethod(
        $this->queryInjector->getConcreteInsertRsvdOrderQuery(),
        $this->getIsValidReservedOrderMethod(),
        $this->getIsConflictingReservedOrderMethod()
      ); 
    }
    return $this->reserveOrderMethod;
  }

  public function getDeleteReservedOrderMethod(): DeleteReservedOrderMethod {
    if ($this->deleteReservedOrderMethod === null) {
      $this->deleteReservedOrderMethod = new DeleteReservedOrderMethod(
        $this->queryInjector->getDeleteByIdQuery(),
        $this->rsvdOrdersTableLoader->load()        
      ); 
    }
    return $this->deleteReservedOrderMethod;
  }

  public function getGetUsersReservedOrdersMethod(): GetUsersReservedOrdersMethod {
    if ($this->getUsersReservedOrdersMethod === null) {
      $this->getUsersReservedOrdersMethod = new GetUsersReservedOrdersMethod(
        $this->queryInjector->getFetchUsersReservedOrdersQuery(),
        $this->queryInjector->getFetchUserByIdQuery() 
      );
    }
    return $this->getUsersReservedOrdersMethod;
  }

  /**
   * Confirm order methods
   */
  public function getConfirmOrderMethod(): ConfirmOrderMethod {
    if ($this->confirmOrderMethod === null) {
      $this->confirmOrderMethod = new ConfirmOrderMethod(
        $this->queryInjector->getFetchRsvdOrderByIdQuery(),
        $this->queryInjector->getFetchIsUserOwnedShortCodeQuery(),
        $this->queryInjector->getConcreteInsertConfirmedOrderQuery(),
        $this->queryInjector->getConcreteInsertEditedVideoOrderQuery(),
        $this->queryInjector->getBatchInsertCellLabelsQuery(),
        $this->queryInjector->getDeleteByIdQuery(),
        $this->cellsLabelTableLoader->load(),
        $this->rsvdOrdersTableLoader->load()
      ); 
    }
    return $this->confirmOrderMethod;
  }
  
  public function getDeleteConfirmedOrderMethod(): DeleteConfirmedOrderMethod {
    if ($this->deleteConfirmedOrderMethod === null) {
      $this->deleteConfirmedOrderMethod = new DeleteConfirmedOrderMethod(
        $this->queryInjector->getDeleteByIdQuery(),
        $this->confirmedOrdersTableLoader->load(),
        $this->queryInjector->getDeleteQuery(),
        $this->cellsLabelTableLoader->load()
      ); 
    }
    return $this->deleteConfirmedOrderMethod;
  }

  public function getUpdateConfirmedOrderMethod(): UpdateConfirmedOrderMethod {
    if ($this->updateConfirmedOrderMethod === null) {
      $this->updateConfirmedOrderMethod = new UpdateConfirmedOrderMethod(
        $this->queryInjector->getUpdateByIdQuery(),
        $this->confirmedOrdersTableLoader->load()
      );
    }
    return $this->updateConfirmedOrderMethod;
  }

  public function getGetUsersConfirmedOrdersAndCellLabelMethod(): GetUsersConfirmedOrdersAndCellLabelsMethod {
    if ($this->getUsersConfirmedOrdersAndCellLabelsMethod === null) {
      $this->getUsersConfirmedOrdersAndCellLabelsMethod = new GetUsersConfirmedOrdersAndCellLabelsMethod(
        $this->queryInjector->getFetchUsersConfirmedOrdersQuery(),
        $this->queryInjector->getFetchConfirmedOrderCellLabelsQuery(),
        $this->queryInjector->getFetchUserByIdQuery()
      ); 
    }
    return $this->getUsersConfirmedOrdersAndCellLabelsMethod;
  }

  public function getGetUsersConfirmedOrdersMethod(): GetUsersConfirmedOrdersMethod {
    if ($this->getUsersConfirmedOrdersMethod === null) {
      $this->getUsersConfirmedOrdersMethod = new GetUsersConfirmedOrdersMethod(
        $this->queryInjector->getFetchUserByIdQuery(),
        $this->queryInjector->getFetchUsersConfirmedOrdersQuery() 
      ); 
    }
    return $this->getUsersConfirmedOrdersMethod;
  }

  /**
   * Cell label method
   */
  public function getUpdateCellLabelMethod(): UpdateCellLabelMethod {
    if ($this->updateCellLabelMethod === null) {
      $this->updateCellLabelMethod = new UpdateCellLabelMethod(
        $this->queryInjector->getUpdateByIdQuery(),
        $this->cellsLabelTableLoader->load() 
      ); 
    }
    return $this->updateCellLabelMethod;
  }
  
  public function getDeleteCellLabelMethod(): DeleteCellLabelMethod {
    if ($this->deleteCellLabelMethod === null) {
      $this->deleteCellLabelMethod = new DeleteCellLabelMethod(
        $this->queryInjector->getDeleteByIdQuery(),
        $this->cellsLabelTableLoader->load()        
      ); 
    }
    return $this->deleteCellLabelMethod;
  }

  /**
   * Create reserved order policy method
   */
  public function getCreateReservedOrderPolicyMethod(): CreateReservedOrderPolicyMethod {
    if ($this->createReservedOrderPolicyMethod === null) {
      $this->createReservedOrderPolicyMethod = new CreateReservedOrderPolicyMethod(
        $this->queryInjector->getConcreteInsertReservedOrderPolicyQuery(),
        $this->queryInjector->getFetchReservedOrderPolicyQuery() 
      );
    }
    return $this->createReservedOrderPolicyMethod;
  }

  public function getMakeVideoUploadPolicyMethod(): MakeVideoUploadPolicyMethod {
    if ($this->makeVideoUploadPolicyMethod === null) {
      $this->makeVideoUploadPolicyMethod = new MakeVideoUploadPolicyMethod(
        $this->queryInjector->getConcreteInsertVideoUploadPolicyQuery(),
        $this->timestampBuilderLoader->load()
      ); 
    }
    return $this->makeVideoUploadPolicyMethod;
  }

  /**
   * Transaction execution methods
   */
  public function getExecuteTransactionsForTimeIntervalMethod(): ExecuteTransactionsForTimeIntervalMethod {
    if ($this->executeTransactionsForTimeIntervalMethod === null) {
      $this->executeTransactionsForTimeIntervalMethod = new ExecuteTransactionsForTimeIntervalMethod(
        $this->queryInjector->getFetchConfirmedOrdersByTimeQuery(),
        $this->queryInjector->getConcreteFetchConfirmedOrderTransactionQuery(),
        $this->getExecuteOrderTransactionMethod(),
        $this->logger,
        $this->timestampBuilderLoader->load(),
        $this->timestampSerializerLoader->load()
      ); 
    }
    return $this->executeTransactionsForTimeIntervalMethod;
  }

  public function getExecuteOrderTransactionMethod(): ExecuteOrderTransactionMethod {
    if ($this->executeOrderTransactionMethod === null) {
      $this->executeOrderTransactionMethod = new ExecuteOrderTransactionMethod(
        $this->logger,
        $this->queryInjector->getFetchShortCodeByIdQuery(),
        $this->queryInjector->getInsertConfirmedOrderTransactionQuery(),
        $this->confirmedOrderTransactionTableLoader->load(),
        $this->queryInjector->getInsertFailedConfirmedOrderTransactionQuery(),
        $this->failedConfirmedOrderTransactionTableLoader->load(),
        $this->timestampSerializerLoader->load(),
        $this->timestampBuilderLoader->load()
      ); 
    }
    return $this->executeOrderTransactionMethod;
  }

  public function getUploadBasicVideoMethod(): UploadBasicVideoMethod {
    if ($this->uploadBasicVideoMethod === null) {
      $this->uploadBasicVideoMethod = new UploadBasicVideoMethod(
        $this->queryInjector->getFetchCompletedBasicVideoSetByCompletedOrderQuery(),
        $this->queryInjector->getFetchCompletedOrderByIdQuery(),
        $this->queryInjector->getFetchConfirmedOrderByIdQuery(),
        $this->queryInjector->getInsertBasicVideoQuery(),
        $this->queryInjector->getInsertCompletedBasicVideoSetQuery(),
        $this->queryInjector->getDeleteByIdQuery(),
        $this->queryInjector->getConcreteFetchVideoUploadPolicyQuery(),
        $this->queryInjector->getConcreteFetchVideoMimeTypesQuery(),
        $this->queryInjector->getCompletedBasicVideoSetTable(),
        $this->queryInjector->getBasicVideosTable(),
        $this->logger,
        $this->timestampBuilderLoader->load(),
        $this->timestampSerializerLoader->load(),
        $this->timeSerializerLoader->load(),
        $this->getBasicVideoPathFormatMethod()
      );
    }
    return $this->uploadBasicVideoMethod;
  }

  public function getBasicVideoPathFormatMethod(): BasicVideoPathFormatMethod {
    if ($this->basicVideoPathFormatMethod === null) {
      $this->basicVideoPathFormatMethod = new BasicVideoPathFormatMethod();  
    }
    return $this->basicVideoPathFormatMethod;
  }

  public function getUploadEditedVideoMethod(): UploadEditedVideoMethod {
    if ($this->uploadEditedVideoMethod === null) {
      $this->uploadEditedVideoMethod = new UploadEditedVideoMethod(
        $this->queryInjector->getFetchEditedVideoOrderByIdQuery(),
        $this->queryInjector->getFetchConfirmedOrderByIdQuery(),
        $this->queryInjector->getFetchCompletedOrderByConfirmedOrderQuery(),
        $this->queryInjector->getFetchCompositeVideoByIdQuery(),
        $this->queryInjector->getConcreteFetchVideoUploadPolicyQuery(),
        $this->queryInjector->getInsertCompositeVideoQuery(),
        $this->queryInjector->getInsertCompletedCompositeVideoQuery(),
        $this->queryInjector->getDeleteByIdQuery(),
        $this->queryInjector->getConcreteFetchVideoMimeTypesQuery(),
        $this->queryInjector->getCompositeVideosTable(),
        $this->queryInjector->getCompletedCompositeVideoTable(),
        $this->logger,
        $this->timestampBuilderLoader->load(),
        $this->timestampSerializerLoader->load(),
        $this->timeSerializerLoader->load(),
        $this->httpUploadedFilesFetcher
      ); 
    }
    return $this->uploadEditedVideoMethod;
  }

  public function getCreateVideoMimeTypeMethod(): CreateVideoMimeTypeMethod {
    if ($this->createVideoMimeTypeMethod === null) {
      $this->createVideoMimeTypeMethod = new CreateVideoMimeTypeMethod(
        $this->queryInjector->getInsertVideoMimeTypeQuery(),
        $this->videoMimeTypesTable
      ); 
    }
    return $this->createVideoMimeTypeMethod;
  }

  public function getCreateShortCodeMethod(): CreateShortCodeMethod {
    if ($this->createShortCodeMethod === null) {
      $this->createShortCodeMethod = new CreateShortCodeMethod(
        $this->queryInjector->getConcreteInsertShortCodeQuery()
      );
    }
    return $this->createShortCodeMethod;
  }

  /**
   * Completed order methods
   */
  public function getCompleteOrderMethod(): CompleteOrderMethod {
    if ($this->completeOrderMethod === null) {
      $this->completeOrderMethod = new CompleteOrderMethod(
        $this->queryInjector->getConcreteInsertCompletedOrderQuery(),
        $this->queryInjector->getFetchConfirmedOrderByIdQuery(),
        $this->logger,
        $this->timestampBuilderLoader->load()
      ); 
    }
    return $this->completeOrderMethod;
  }

  public function getGetUsersCompletedOrdersMethod(): GetUsersCompletedOrdersMethod {
    if ($this->getUsersCompletedOrdersMethod === null) {
      $this->getUsersCompletedOrdersMethod = new GetUsersCompletedOrdersMethod(
        $this->queryInjector->getFetchUserByIdQuery(),
        $this->queryInjector->getFetchUsersConfirmedOrdersQuery(),
        $this->queryInjector->getFetchCompletedOrderByConfirmedOrderQuery() 
      ); 
    }
    return $this->getUsersCompletedOrdersMethod;
  }

  public function getAssignUserPrivilegesMethod(): AssignUserPrivilegesMethod {
    if ($this->assignUserPrivilegesMethod === null) {
      $this->assignUserPrivilegesMethod = new AssignUserPrivilegesMethod(
        $this->queryInjector->getConcreteInsertUserUserPrivilegeEdgeQuery()
      ); 
    }
    return $this->assignUserPrivilegesMethod;
  }

  public function getCreateUserPrivilegesMethod(): CreateUserPrivilegesMethod {
    if ($this->createUserPrivilegesMethod === null) {
      $this->createUserPrivilegesMethod = new CreateUserPrivilegesMethod(
        $this->queryInjector->getConcreteInsertUserPrivilegeQuery()
      ); 
    }
    return $this->createUserPrivilegesMethod;
  }

  public function getCheckUserPrivilegeMethod(): CheckUserPrivilegeMethod {
    if ($this->checkUserPrivilegeMethod === null) {
      $this->checkUserPrivilegeMethod = new CheckUserPrivilegeMethod(
        $this->queryInjector->getFetchUserByIdQuery(),
        $this->queryInjector->getFetchUsersPrivilegesQuery()
      ); 
    }
    return $this->checkUserPrivilegeMethod;
  }

  public function getGetUserAgentMethod(): GetUserAgentMethod {
    if ($this->getUserAgentMethod === null) {
      $this->getUserAgentMethod = new GetUserAgentMethod(
        $this->queryInjector->getFetchUserByIdQuery(),
        $this->queryInjector->getFetchUsersPrivilegesQuery()
      ); 
    }
    return $this->getUserAgentMethod;
  }
}
