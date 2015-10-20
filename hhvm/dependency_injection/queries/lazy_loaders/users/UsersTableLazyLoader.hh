<?hh // strict

class UsersTableLazyLoader extends LazyLoader<UsersTable> {

  protected function make(): UsersTable {
    return new UsersTable();
  }
}
