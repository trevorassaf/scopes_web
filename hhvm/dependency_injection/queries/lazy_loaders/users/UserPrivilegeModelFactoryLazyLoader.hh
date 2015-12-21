<?hh // strict

class UserPrivilegeModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<UserPrivilege>> {

  protected function make(): ConcreteModelFactory<UserPrivilege> {
    return new UserPrivilegeFactory();
  }
}
