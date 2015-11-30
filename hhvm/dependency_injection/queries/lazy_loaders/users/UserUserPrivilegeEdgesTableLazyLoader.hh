<?hh // strict

class UserUserPrivilegeEdgesTableLazyLoader extends LazyLoader<UserUserPrivilegeEdgesTable> {

  protected function make(): UserUserPrivilegeEdgesTable {
    return new UserUserPrivilegeEdgesTable();
  }
}
