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

  public function __construct(
    private QueryInjector $queryInjector,
    private LazyLoader<UsersTable> $usersTableLoader,
    private LazyLoader<RegularWeekDaysTable> $regularWeekDaysTableLoader,
    private LazyLoader<RegularTimesTable> $regularTimesTableLoader,
    private LazyLoader<RegularWeekDayRegularTimeEdgesTable> $regularEdgesTableLoader,
    private LazyLoader<IrregularDatesTable> $irregularDatesTableLoader,
    private LazyLoader<IrregularTimesTable> $irregularTimesTableLoader
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
}
