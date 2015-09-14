<?hh // strict

class ProductionQueryInjectorFactory extends SingletonQueryInjectorFactory {

  protected function makeQueryInjector(): QueryInjector {
    $users_table_loader = new UsersTableLazyLoader(); 
    $regular_times_table_loader = new RegularTimesTableLazyLoader();
    $regular_edge_table_loader = new RegularWeekDayRegularTimeEdgesTableLazyLoader();

    return new QueryInjector(
      new AsyncMysqlConnectionLazyLoader(
        new ProductionAsyncMysqlConnectionFactory()
      ),
      new ConstraintMapToConjunctiveWhereClauseTranslatorLazyLoader(),
      $users_table_loader,
      new UserModelFactoryLazyLoader($users_table_loader),
      new InsertQueryCreaterLazyLoader(),
      new RegularWeekDaysTableLazyLoader(),
      new RegularWeekDayModelFactoryLazyLoader(),
      $regular_times_table_loader,
      new RegularTimeModelFactoryLazyLoader(
        $regular_times_table_loader
      ),
      $regular_edge_table_loader,
      new RegularWeekDayRegularTimeEdgeModelFactoryLazyLoader(
        $regular_edge_table_loader
      )
    );
  }
}
