<?hh // strict

class ProductionQueryInjectorFactory extends SingletonQueryInjectorFactory {

  protected function makeQueryInjector(): QueryInjector {
    $users_table_loader = new UsersTableLazyLoader(); 
    return new QueryInjector(
      new AsyncMysqlConnectionLazyLoader(
        new ProductionAsyncMysqlConnectionFactory()
      ),
      new ConstraintMapToConjunctiveWhereClauseTranslatorLazyLoader(),
      $users_table_loader,
      new UserModelFactoryLazyLoader($users_table_loader),
      new InsertQueryCreaterLazyLoader()
    );
  }
}
