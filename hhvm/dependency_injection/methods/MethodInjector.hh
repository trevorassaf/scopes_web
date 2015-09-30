<?hh // strict

class MethodInjector {

  // User methods
  private ?CreateUserMethod $createUserMethod;

  private ?GetUserByEmailMethod $getUserByEmailMethod;

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

  // Confirm order method
  private ?ConfirmOrderMethod $confirmOrderMethod;
  private ?UpdateConfirmedOrderMethod $updateConfirmedOrderMethod;
  private ?DeleteConfirmedOrderMethod $deleteConfirmedOrderMethod;
  private ?GetUsersConfirmedOrdersAndCellLabelsMethod $getUsersConfirmedOrdersAndCellLabelsMethod;

  // Cell label methods
  private ?UpdateCellLabelMethod $updateCellLabelMethod;
  private ?DeleteCellLabelMethod $deleteCellLabelMethod;

  private ?CreateReservedOrderPolicyMethod $createReservedOrderPolicyMethod;

  public function __construct(
    private QueryInjector $queryInjector,
    private LazyLoader<UsersTable> $usersTableLoader,
    private LazyLoader<RegularWeekDaysTable> $regularWeekDaysTableLoader,
    private LazyLoader<RegularTimesTable> $regularTimesTableLoader,
    private LazyLoader<RegularWeekDayRegularTimeEdgesTable> $regularEdgesTableLoader,
    private LazyLoader<IrregularDatesTable> $irregularDatesTableLoader,
    private LazyLoader<IrregularTimesTable> $irregularTimesTableLoader,
    private LazyLoader<CellLabelsTable> $cellsLabelTableLoader,
    private LazyLoader<TimestampSerializer> $timestampSerializerLoader,
    private LazyLoader<TimeSerializer> $timeSerializerLoader,
    private LazyLoader<DateSerializer> $dateSerializerLoader,
    private LazyLoader<TimestampBuilder> $timestampBuilderLoader,
    private LazyLoader<DateToDayOfTheWeekConverter> $dateToDayOfTheWeekConverterLoader,
    private LazyLoader<TimestampSegmentExpander> $timestampSegmentExpanderLoader,
    private LazyLoader<ConfirmedOrdersTable> $confirmedOrdersTableLoader,
    private LazyLoader<RsvdOrdersTable> $rsvdOrdersTableLoader,
    private Logger $logger
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
        $this->logger
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
   * Reserve order method
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

  /**
   * Confirm order method
   */
  public function getConfirmOrderMethod(): ConfirmOrderMethod {
    if ($this->confirmOrderMethod === null) {
      $this->confirmOrderMethod = new ConfirmOrderMethod(
        $this->queryInjector->getFetchRsvdOrderByIdQuery(),
        $this->queryInjector->getConcreteInsertConfirmedOrderQuery(),
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

}
