<?hh // strict

class UserModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<User>> {

  public function __construct(
    private LazyLoader<UsersTable> $usersTableLazyLoader  
  ) {}

  protected function make(): ConcreteModelFactory<User> {
    return new UserFactory($this->usersTableLazyLoader->load());
  }
}
