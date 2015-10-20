<?hh // strict

class UserModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<User>> {

  public function __construct(
    private LazyLoader<UsersTable> $usersTableLazyLoader,
    private LazyLoader<TimestampSerializer> $timestampSerializerLoader
  ) {}

  protected function make(): ConcreteModelFactory<User> {
    return new UserFactory(
      $this->timestampSerializerLoader->load(),
      $this->usersTableLazyLoader->load()
    );
  }
}
