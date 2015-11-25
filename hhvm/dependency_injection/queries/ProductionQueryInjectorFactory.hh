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
    $timestamp_segment_factory_lazy_loader = new TimestampSegmentFactoryLazyLoader(
      $timestamp_serializer_loader
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
    $short_code_table_loader = new ShortCodesTableLazyLoader();
    $edited_video_order_table_loader = new EditedVideoOrderTableLazyLoader();
    $basic_video_table_loader = new BasicVideosTableLazyLoader();
    $composite_video_table_loader = new CompositeVideoTableLazyLoader();
    $confirmed_order_transaction_table_loader = new ConfirmedOrderTransactionTableLazyLoader();
    $failed_confirmed_order_transaction_table_loader = new FailedConfirmedOrderTransactionTableLazyLoader();
    $order_transaction_policy_table_loader = new OrderTransactionPolicyTableLazyLoader();
    $completed_orders_table_loader = new CompletedOrdersTableLazyLoader();
    $completed_basic_video_set_table_loader = new CompletedBasicVideoSetTableLazyLoader();
    $video_upload_policy_table_loader = new VideoUploadPolicyTableLazyLoader();
    $video_mime_type_table_loader = new VideoMimeTypesTableLazyLoader();
    $completed_composite_video_table_loader = new CompletedCompositeVideoTableLazyLoader();

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
        $timestamp_serializer_loader,
        $timestamp_segment_factory_lazy_loader
      ),
      $confirmed_orders_table_loader,
      new ConfirmedOrderModelFactoryLazyLoader(
        $confirmed_orders_table_loader,
        $timestamp_serializer_loader,
        $timestamp_segment_factory_lazy_loader
      ),
      $rsvd_order_policy_table_loader,
      new ReservedOrderPolicyModelFactoryLazyLoader(
        $rsvd_order_policy_table_loader
      ),
      $cell_labels_table_loader,
      new CellLabelModelFactoryLazyLoader(
        $cell_labels_table_loader
      ),
      $query_exception_factory,
      $short_code_table_loader,
      new ShortCodeModelFactoryLazyLoader(
        $short_code_table_loader
      ),
      $edited_video_order_table_loader,
      new EditedVideoOrderModelFactoryLazyLoader(
        $edited_video_order_table_loader
      ),
      $basic_video_table_loader,
      new BasicVideoModelFactoryLazyLoader(
        $basic_video_table_loader
      ),
      $composite_video_table_loader,
      new CompositeVideoModelFactoryLazyLoader(
        $timestamp_serializer_loader,
        $time_serializer_loader,
        $composite_video_table_loader
      ),
      $confirmed_order_transaction_table_loader,
      new ConfirmedOrderTransactionModelFactoryLazyLoader(
        $confirmed_order_transaction_table_loader,
        $timestamp_serializer_loader
      ),
      $failed_confirmed_order_transaction_table_loader,
      new FailedConfirmedOrderTransactionModelFactoryLazyLoader(
        $failed_confirmed_order_transaction_table_loader,
        $timestamp_serializer_loader
      ),
      $order_transaction_policy_table_loader,
      new OrderTransactionPolicyModelFactoryLazyLoader(
        $timestamp_serializer_loader,
        $order_transaction_policy_table_loader
      ),
      $completed_orders_table_loader,
      new CompletedOrderModelFactoryLazyLoader(
        $completed_orders_table_loader,
        $timestamp_serializer_loader
      ),
      $completed_basic_video_set_table_loader,
      new CompletedBasicVideoSetModelFactoryLazyLoader(
        $completed_basic_video_set_table_loader,
        $timestamp_serializer_loader
      ),
      $video_upload_policy_table_loader,
      new VideoUploadPolicyModelFactoryLazyLoader(
        $video_upload_policy_table_loader,
        $timestamp_serializer_loader
      ),
      $video_mime_type_table_loader,
      new VideoMimeTypeModelFactoryLazyLoader(
        $video_mime_type_table_loader
      ),
      $completed_composite_video_table_loader,
      new CompletedCompositeVideoModelFactoryLazyLoader(
        $completed_composite_video_table_loader,
        $timestamp_serializer_loader
      )
    );
  }
}
