<?hh // strict

class MethodInjector {

  // User methods
  private ?CreateUserMethod $createUserMethod;

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

  // Confirm order method
  private ?ConfirmOrderMethod $confirmOrderMethod;

  private ?CreateReservedOrderPolicyMethod $createReservedOrderPolicyMethod;

  public function __construct(
    private QueryInjector $queryInjector,
    private LazyLoader<UsersTable> $usersTableLoader,
    private LazyLoader<RegularWeekDaysTable> $regularWeekDaysTableLoader,
    private LazyLoader<RegularTimesTable> $regularTimesTableLoader,
    private LazyLoader<RegularWeekDayRegularTimeEdgesTable> $regularEdgesTableLoader,
    private LazyLoader<IrregularDatesTable> $irregularDatesTableLoader,
    private LazyLoader<IrregularTimesTable> $irregularTimesTableLoader,
    private LazyLoader<CellLabelsTable> $cellsLabelTableLoader
  ) {}

  public function getCreateUserMethod(): CreateUserMethod {
    if ($this->createUserMethod === null) {
      $this->createUserMethod = new CreateUserMethod(
        $this->queryInjector->getConcreteInsertUserQuery(),
        $this->queryInjector->getFetchUserByUniqueKeyQuery(),
        $this->usersTableLoader->load()
      );
    }       
    return $this->createUserMethod;
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
        $this->regularTimesTableLoader->load()
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
        $this->irregularDatesTableLoader->load() 
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
        $this->queryInjector->getFetchReservedOrderPolicyQuery()
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
        $this->getIsConflictingReservedOrderMethod(),
        $this->queryInjector->getFetchRegularEdgeQuery(),
        $this->regularEdgesTableLoader->load(),
        $this->queryInjector->getFetchRegularTimeQuery(),
        $this->regularTimesTableLoader->load(),
        $this->queryInjector->getConcreteFetchIrregularTimeQuery(),
        $this->queryInjector->getFetchIrregularDateByUniqueKeyQuery(),
        $this->irregularDatesTableLoader->load()
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
        $this->getIsValidReservedOrderMethod()
      ); 
    }
    return $this->reserveOrderMethod;
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
        $this->queryInjector->getDeleteRsvdOrderByIdQuery(),
        $this->cellsLabelTableLoader->load()
      ); 
    }
    return $this->confirmOrderMethod;
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
