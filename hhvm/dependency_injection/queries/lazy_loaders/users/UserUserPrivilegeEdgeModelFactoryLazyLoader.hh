<?hh // strict

class UserUserPrivilegeEdgeModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<UserUserPrivilegeEdge>> {

  public function __construct(
    private LazyLoader<UserUserPrivilegeEdgesTable> $tableLoader
  ) {} 

  protected function make(): ConcreteModelFactory<UserUserPrivilegeEdge> {
    return new UserUserPrivilegeEdgeModelFactory(
      $this->tableLoader->load()
    );
  }
}
