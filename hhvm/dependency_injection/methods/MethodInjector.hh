<?hh // strict

class MethodInjector {

  // File methodds
  private ?DeleteFileMethod $deleteFileMethod;

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
  private ?GetAvailablePhysicalScopesMethod $getAvailablePhysicalScopesMethod;

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
  private ?IsConflictingConfirmedOrderMethod $isConflictingConfirmedOrderMethod;
  private ?GetAllConfirmedOrdersMethod $getAllConfirmedOrdersMethod;
  private ?GetConfirmedOrderDatesMethod $getConfirmedOrderDatesMethod;
  private ?CreateOrderStatusMethod $createOrderStatusMethod;
  private ?CreatePaymentStatusMethod $createPaymentStatusMethod;

  // Cell label methods
  private ?UpdateCellLabelMethod $updateCellLabelMethod;
  private ?DeleteCellLabelMethod $deleteCellLabelMethod;

  // Policy methods
  private ?CreateReservedOrderPolicyMethod $createReservedOrderPolicyMethod;
  private ?MakeVideoUploadPolicyMethod $makeVideoUploadPolicyMethod;
  private ?GetOrderConfigurationMethod $getOrderConfigurationMethod;
  private ?CreateOrderConfigurationMethod $createOrderConfigurationMethod;

  // Transaction methods
  private ?ExecuteTransactionsForTimeIntervalMethod $executeTransactionsForTimeIntervalMethod;
  private ?ExecuteOrderTransactionMethod $executeOrderTransactionMethod;

  // Video methods
  private ?UploadBasicVideoMethod $uploadBasicVideoMethod;
  private ?BasicVideoPathFormatMethod $basicVideoPathFormatMethod;
  private ?UploadEditedVideoMethod $uploadEditedVideoMethod;
  private ?CompositeVideoPathFormatMethod $compositeVideoPathFormatMethod;
  private ?CreateVideoMimeTypeMethod $createVideoMimeTypeMethod;
  private ?MarkBasicVideoDownloadedMethod $markBasicVideoDownloadedMethod;
  private ?IsBasicVideoDownloadedMethod $isBasicVideoDownloadedMethod;
  private ?DeleteBasicVideoMethod $deleteBasicVideoMethod;
  private ?MakeBasicVideoPathMethod $makeBasicVideoPathMethod;

  // Short code methods
  private ?CreateShortCodeMethod $createShortCodeMethod;
  private ?GetUsersShortCodesMethod $getUsersShortCodesMethod;
  private ?GetShortCodeByIdMethod $getShortCodeByIdMethod;

  // Complete order methods
  private ?CompleteOrderMethod $completeOrderMethod;
  private ?GetUsersCompletedOrdersMethod $getUsersCompletedOrdersMethod;

  // Gen0 Order Price Policy
  private ?CreateGen0OrderPricePolicyMethod $createGen0OrderPricePolicyMethod; 
  private ?GetGen0OrderPricePolicyByTimeMethod $getGen0OrderPricePolicyByTimeMethod;
  private ?ApplyGen0OrderPricePolicyMethod $applyGen0OrderPricePolicyMethod;

  // Chronos
  private ?GetDisallowedWeekDaysMethod $getDisallowedWeekDaysMethod;

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
    private LazyLoader<TimestampOperator> $timestampOperatorLoader,
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
  public function getGetAvailablePhysicalScopesMethod(): GetAvailablePhysicalScopesMethod {
    if ($this->getAvailablePhysicalScopesMethod === null) {
      $this->getAvailablePhysicalScopesMethod = new GetAvailablePhysicalScopesMethod(
        $this->queryInjector->getFetchRsvdOrdersByTimeQuery(),
        $this->queryInjector->getFetchConfirmedOrdersByTimeQuery(),
        $this->queryInjector->getFetchReservedOrderPolicyQuery(),
        $this->logger,
        $this->timestampSegmentFactoryLoader->load(),
        $this->queryInjector->getFetchScopeMappingsByReservedOrderQuery(),
        $this->queryInjector->getFetchScopeMappingsByConfirmedOrderQuery()
      ); 
    } 
    return $this->getAvailablePhysicalScopesMethod;
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
        $this->getGetAvailablePhysicalScopesMethod(),
        $this->queryInjector->getConcreteInsertReservedOrderScopeMappingsQuery()
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
        $this->queryInjector->getFetchIsUserOwnedShortCodeQuery(),
        $this->queryInjector->getConcreteInsertConfirmedOrderQuery(),
        $this->getApplyGen0OrderPricePolicyMethod(),
        $this->getIsConflictingConfirmedOrderMethod(),
        $this->timestampSegmentFactoryLoader->load(),
        $this->timestampBuilderLoader->load(),
        $this->timestampOperatorLoader->load()
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

  public function getIsConflictingConfirmedOrderMethod(): IsConflictingConfirmedOrderMethod {
    if ($this->isConflictingConfirmedOrderMethod === null) {
      $this->isConflictingConfirmedOrderMethod = new IsConflictingConfirmedOrderMethod(
        $this->queryInjector->getFetchConfirmedOrdersByTimeQuery(),
        $this->queryInjector->getFetchReservedOrderPolicyQuery()
      );
    }
    return $this->isConflictingConfirmedOrderMethod;
  }

  public function getGetAllConfirmedOrdersMethod(): GetAllConfirmedOrdersMethod {
    if ($this->getAllConfirmedOrdersMethod === null) {
      $this->getAllConfirmedOrdersMethod = new GetAllConfirmedOrdersMethod(
        $this->queryInjector->getFetchConfirmedOrdersByTimeQuery(),
        $this->queryInjector->getFetchConfirmedOrderQuery()
      );
    }
    return $this->getAllConfirmedOrdersMethod;
  }

  public function getGetConfirmedOrdersDatesMethod(): GetConfirmedOrderDatesMethod {
    if ($this->getConfirmedOrderDatesMethod === null) {
      $this->getConfirmedOrderDatesMethod = new GetConfirmedOrderDatesMethod(
        $this->getGetAllConfirmedOrdersMethod()
      );
    }
    return $this->getConfirmedOrderDatesMethod;
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

  public function getCompositeVideoPathFormatMethod(): CompositeVideoPathFormatMethod {
    if ($this->compositeVideoPathFormatMethod === null) {
      $this->compositeVideoPathFormatMethod = new CompositeVideoPathFormatMethod(); 
    }
    return $this->compositeVideoPathFormatMethod;
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
        $this->queryInjector->getFetchCompletedCompositeVideoByEditedVideoOrderQuery(),
        $this->getCompositeVideoPathFormatMethod()
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

  public function getGetUsersShortCodesMethod(): GetUsersShortCodesMethod {
    if ($this->getUsersShortCodesMethod === null) {
      $this->getUsersShortCodesMethod = new GetUsersShortCodesMethod(
        $this->queryInjector->getFetchUserByIdQuery(),
        $this->queryInjector->getFetchUserShortCodesQuery()
      ); 
    }
    return $this->getUsersShortCodesMethod;
  }

  public function getGetShortCodeByIdMethod(): GetShortCodeByIdMethod {
    if ($this->getShortCodeByIdMethod === null) {
      $this->getShortCodeByIdMethod = new GetShortCodeByIdMethod(
        $this->queryInjector->getFetchShortCodeByIdQuery()
      ); 
    }
    return $this->getShortCodeByIdMethod;
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

  public function getMarkBasicVideoDownloadedMethod(): MarkBasicVideoDownloadedMethod {
    if ($this->markBasicVideoDownloadedMethod === null) {
      $this->markBasicVideoDownloadedMethod = new MarkBasicVideoDownloadedMethod(
        $this->queryInjector->getConcreteInsertBasicVideoDownloadReceiptQuery(),
        $this->timestampBuilderLoader->load()
      ); 
    }
    return $this->markBasicVideoDownloadedMethod;
  }

  public function getIsBasicVideoDownloadedMethod(): IsBasicVideoDownloadedMethod {
    if ($this->isBasicVideoDownloadedMethod === null) {
      $this->isBasicVideoDownloadedMethod = new IsBasicVideoDownloadedMethod(
        $this->queryInjector->getFetchDownloadReceiptsForBasicVideoQuery() 
      ); 
    }
    return $this->isBasicVideoDownloadedMethod;
  }

  public function getDeleteBasicVideoMethod(): DeleteBasicVideoMethod {
    if ($this->deleteBasicVideoMethod === null) {
      $this->deleteBasicVideoMethod = new DeleteBasicVideoMethod(
        $this->queryInjector->getFetchBasicVideoByIdQuery(),
        $this->queryInjector->getFetchCompletedBasicVideoSetByIdQuery(),
        $this->queryInjector->getFetchCompletedOrderByIdQuery(),
        $this->queryInjector->getFetchConfirmedOrderByIdQuery(),
        $this->queryInjector->getConcreteFetchVideoUploadPolicyQuery(),
        $this->queryInjector->getDeleteByIdQuery(),
        $this->queryInjector->getBasicVideosTable(),
        $this->getMakeBasicVideoPathMethod(),
        $this->getDeleteFileMethod()
      );
    }
    return $this->deleteBasicVideoMethod;
  }

  public function getMakeBasicVideoPathMethod(): MakeBasicVideoPathMethod {
    if ($this->makeBasicVideoPathMethod === null) {
      $this->makeBasicVideoPathMethod = new MakeBasicVideoPathMethod(
        $this->queryInjector->getConcreteFetchVideoUploadPolicyQuery(),
        $this->getBasicVideoPathFormatMethod(),
        $this->queryInjector->getFetchVideoMimeTypeByIdQuery() 
      ); 
    }
    return $this->makeBasicVideoPathMethod;
  }

  public function getDeleteFileMethod(): DeleteFileMethod {
    if ($this->deleteFileMethod === null) {
      $this->deleteFileMethod = new DeleteFileMethod(); 
    }
    return $this->deleteFileMethod;
  }

  public function getCreateGen0OrderPricePolicyMethod(): CreateGen0OrderPricePolicyMethod {
    if ($this->createGen0OrderPricePolicyMethod === null) {
      $this->createGen0OrderPricePolicyMethod = new CreateGen0OrderPricePolicyMethod(
        $this->queryInjector->getConcreteInsertGen0OrderPricePolicyQuery(),
        $this->timestampBuilderLoader->load()
      ); 
    }
    return $this->createGen0OrderPricePolicyMethod;
  }

  public function getGetGen0OrderPricePolicyMethod(): GetGen0OrderPricePolicyByTimeMethod {
    if ($this->getGen0OrderPricePolicyByTimeMethod === null) {
      $this->getGen0OrderPricePolicyByTimeMethod = new GetGen0OrderPricePolicyByTimeMethod(
        $this->queryInjector->getFetchGen0OrderPricePolicyByTimeQuery(),
        $this->timestampBuilderLoader->load()
      );
    }
    return $this->getGen0OrderPricePolicyByTimeMethod;
  }

  public function getApplyGen0OrderPricePolicyMethod(): ApplyGen0OrderPricePolicyMethod {
    if ($this->applyGen0OrderPricePolicyMethod === null) {
      $this->applyGen0OrderPricePolicyMethod = new ApplyGen0OrderPricePolicyMethod(
        $this->getGetGen0OrderPricePolicyMethod()
      ); 
    }
    return $this->applyGen0OrderPricePolicyMethod;
  }

  public function getGetOrderConfigurationMethod(): GetOrderConfigurationMethod {
    if ($this->getOrderConfigurationMethod === null) {
      $this->getOrderConfigurationMethod = new GetOrderConfigurationMethod(
        $this->queryInjector->getConcreteFetchOrderConfigurationQuery(),
        $this->timestampBuilderLoader->load()
      );
    }
    return $this->getOrderConfigurationMethod;
  }

  public function getCreateOrderConfigurationMethod(): CreateOrderConfigurationMethod {
    if ($this->createOrderConfigurationMethod === null) {
      $this->createOrderConfigurationMethod = new CreateOrderConfigurationMethod(
        $this->queryInjector->getConcreteInsertOrderConfigurationQuery(),
        $this->timestampBuilderLoader->load()
      ); 
    }
    return $this->createOrderConfigurationMethod;
  }

  public function getGetDisallowedWeekDaysMethod(): GetDisallowedWeekDaysMethod {
    if ($this->getDisallowedWeekDaysMethod === null) {
      $this->getDisallowedWeekDaysMethod = new GetDisallowedWeekDaysMethod(
        $this->queryInjector->getFetchAllRegularWeekDaysQuery()
      ); 
    }
    return $this->getDisallowedWeekDaysMethod;
  }

  public function getCreateOrderStatusMethod(): CreateOrderStatusMethod {
    if ($this->createOrderStatusMethod === null) {
      $this->createOrderStatusMethod = new CreateOrderStatusMethod(
        $this->queryInjector->getInsertOrderStatusQuery(),
        $this->queryInjector->getOrderStatusTable()
      ); 
    }
    return $this->createOrderStatusMethod;
  }

  public function getCreatePaymentStatusMethod(): CreatePaymentStatusMethod {
    if ($this->createPaymentStatusMethod === null) {
      $this->createPaymentStatusMethod = new CreatePaymentStatusMethod(
        $this->queryInjector->getInsertPaymentStatusQuery(),
        $this->queryInjector->getPaymentStatusTable()
      ); 
    }
    return $this->createPaymentStatusMethod;
  }

  public function getTimeSerializer(): TimeSerializer {
    return $this->timeSerializerLoader->load();
  }

  public function getTimestampOperator(): TimestampOperator {
    return $this->timestampOperatorLoader->load();
  }
}
