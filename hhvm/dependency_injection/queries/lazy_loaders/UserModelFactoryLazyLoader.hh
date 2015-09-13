<?hh // strict

class UserModelFactoryLazyLoader extends LazyLoader<ModelFactory<User>> {

  public function __construct(
    private LazyLoader<UsersTable> $usersTableLazyLoader  
  ) {}

  protected function make(): ModelFactory<User> {
    return new UserFactory($this->usersTableLazyLoader->load());
  }
}
