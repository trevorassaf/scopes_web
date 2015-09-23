<?hh // strict

class ProductionQueryInjectorFactory extends SingletonQueryInjectorFactory {

  protected function makeQueryInjector(): QueryInjector {
    // Query core components 
    $query_exception_factory = new QueryExceptionFactoryLazyLoader();

    // Utils
    $date_serializer_loader = new HRDateSerializerLazyLoader(); 
    $time_serializer_loader = new HRTimeSerializerLazyLoader();
    $timestamp_serializer_loader = new HRTimestampSerializerLazyLoader(
      $date_serializer_loader,
      $time_serializer_loader
    );

    // Tables
    $users_table_loader = new UsersTableLazyLoader(); 
    $regular_times_table_loader = new RegularTimesTableLazyLoader();
    $regular_edge_table_loader = new RegularWeekDayRegularTimeEdgesTableLazyLoader();
    $irregular_times_table_loader = new IrregularTimesTableLazyLoader();
    $irregular_dates_table_loader = new IrregularDatesTableLazyLoader();
    $rsvd_orders_table_loader = new ReservedOrdersTableLazyLoader();
    $confirmed_orders_table_loader = new ConfirmedOrdersTableLazyLoader();
    $rsvd_order_policy_table_loader = new ReservedOrderPolicyTableLazyLoader();
    $cell_labels_table_loader = new CellLabelsTableLazyLoader();

    return new QueryInjector(
      new AsyncMysqlConnectionLazyLoader(
        new ProductionAsyncMysqlConnectionFactory()
      ),
      new ConstraintMapToConjunctiveWhereClauseTranslatorLazyLoader(),
      $date_serializer_loader,
      $time_serializer_loader,
      $timestamp_serializer_loader,
      $users_table_loader,
      new UserModelFactoryLazyLoader(
        $users_table_loader,
        $timestamp_serializer_loader
      ),
      new InsertQueryCreaterLazyLoader(),
      new RegularWeekDaysTableLazyLoader(),
      new RegularWeekDayModelFactoryLazyLoader(),
      $regular_times_table_loader,
      new RegularTimeModelFactoryLazyLoader(
        $time_serializer_loader,
        $regular_times_table_loader
      ),
      $regular_edge_table_loader,
      new RegularWeekDayRegularTimeEdgeModelFactoryLazyLoader(
        $regular_edge_table_loader
      ),
      $irregular_dates_table_loader,
      new IrregularDateModelFactoryLazyLoader(
        $date_serializer_loader,
        $irregular_dates_table_loader
      ),
      $irregular_times_table_loader,
      new IrregularTimeModelFactoryLazyLoader(
        $time_serializer_loader,
        $irregular_times_table_loader
      ),
      $rsvd_orders_table_loader,
      new ReservedOrderModelFactoryLazyLoader(
        $rsvd_orders_table_loader,
        $timestamp_serializer_loader
      ),
      $confirmed_orders_table_loader,
      new ConfirmedOrderModelFactoryLazyLoader(
        $confirmed_orders_table_loader,
        $timestamp_serializer_loader
      ),
      $rsvd_order_policy_table_loader,
      new ReservedOrderPolicyModelFactoryLazyLoader(
        $rsvd_order_policy_table_loader
      ),
      $cell_labels_table_loader,
      new CellLabelModelFactoryLazyLoader(
        $cell_labels_table_loader
      ),
      $query_exception_factory
    );
  }
}
