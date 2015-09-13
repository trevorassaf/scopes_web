<?hh // strict

class MethodInjector {

  private ?CreateUserMethod $createUserMethod;

  public function __construct(
    private QueryInjector $queryInjector,
    private LazyLoader<UsersTable> $usersTableLoader
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

}
