<?hh // strict

class ProductionQueryInjectorFactory extends SingletonQueryInjectorFactory {

  protected function makeQueryInjector(): QueryInjector {
    $users_table_loader = new UsersTableLazyLoader(); 
    $regular_times_table_loader = new RegularTimesTableLazyLoader();
    $regular_edge_table_loader = new RegularWeekDayRegularTimeEdgesTableLazyLoader();
    $irregular_times_table_loader = new IrregularTimesTableLazyLoader();
    $irregular_dates_table_loader = new IrregularDatesTableLazyLoader();
    $rsvd_orders_table_loader = new ReservedOrdersTableLazyLoader();
    $confirmed_orders_table_loader = new ConfirmedOrdersTableLazyLoader();
    $rsvd_order_policy_table_loader = new ReservedOrderPolicyTableLazyLoader();

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
      ),
      $irregular_dates_table_loader,
      new IrregularDateModelFactoryLazyLoader(
        $irregular_dates_table_loader
      ),
      $irregular_times_table_loader,
      new IrregularTimeModelFactoryLazyLoader(
        $irregular_times_table_loader
      ),
      $rsvd_orders_table_loader,
      new ReservedOrderModelFactoryLazyLoader(
        $rsvd_orders_table_loader
      ),
      $confirmed_orders_table_loader,
      new ConfirmedOrderModelFactoryLazyLoader(
        $confirmed_orders_table_loader
      ),
      $rsvd_order_policy_table_loader,
      new ReservedOrderPolicyModelFactoryLazyLoader(
        $rsvd_order_policy_table_loader
      )
    );
  }
}
