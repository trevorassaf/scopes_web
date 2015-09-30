<?hh // strict

class ProductionMethodInjectorFactory extends SingletonMethodInjectorFactory {

  public function __construct(
    private Logger $logger
  ) {}

  protected function make(): MethodInjector {
    $production_query_injector_factory = new ProductionQueryInjectorFactory();
    $hr_time_serializer_loader = new HRTimeSerializerLazyLoader();
    $hr_date_serializer_loader = new HRDateSerializerLazyLoader();
    $hr_timestamp_serializer_loader = new HRTimestampSerializerLazyLoader(
        $hr_date_serializer_loader,
        $hr_time_serializer_loader
      );
    $hr_timestamp_builder_loader = new TimestampBuilderLazyLoader(
      $hr_timestamp_serializer_loader
    );
    $date_to_week_day_converter_laoder = new DateToDayOfTheWeekConverterLazyLoader(
      $hr_date_serializer_loader
    );
    $timestamp_segment_expander_loader = new TimestampSegmentExpanderLazyLoader(
      $hr_date_serializer_loader
    );
    
    return new MethodInjector(
      $production_query_injector_factory->get(),
      new UsersTableLazyLoader(),
      new RegularWeekDaysTableLazyLoader(),
      new RegularTimesTableLazyLoader(),
      new RegularWeekDayRegularTimeEdgesTableLazyLoader(),
      new IrregularDatesTableLazyLoader(),
      new IrregularTimesTableLazyLoader(),
      new CellLabelsTableLazyLoader(),
      $hr_timestamp_serializer_loader,
      $hr_time_serializer_loader,
      $hr_date_serializer_loader,
      $hr_timestamp_builder_loader,
      $date_to_week_day_converter_laoder,
      $timestamp_segment_expander_loader,
      new ConfirmedOrdersTableLazyLoader(),
      new ReservedOrdersTableLazyLoader(),
      $this->logger
    ); 
  }
}
