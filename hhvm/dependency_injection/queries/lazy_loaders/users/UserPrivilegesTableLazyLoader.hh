<?hh // strict

class UserPrivilegesTableLazyLoader extends LazyLoader<UserPrivilegesTable> {

  protected function make(): UserPrivilegesTable {
    return new UserPrivilegesTable();
  }
}
