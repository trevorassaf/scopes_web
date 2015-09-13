<?hh // strict

class MethodInjector {

  // User methods
  private ?CreateUserMethod $createUserMethod;

  // Regular week day methods
  private ?CreateRegularWeekDayMethod $createRegularWeekDayMethod;

  // Regular time methods
  private ?CreateRegularTimeMethod $createRegularTimeMethod;

  public function __construct(
    private QueryInjector $queryInjector,
    private LazyLoader<UsersTable> $usersTableLoader,
    private LazyLoader<RegularWeekDaysTable> $regularWeekDaysTableLoader,
    private LazyLoader<RegularTimesTable> $regularTimesTableLoader
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
}
