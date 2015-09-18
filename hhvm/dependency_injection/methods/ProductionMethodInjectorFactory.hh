<?hh // strict

class ProductionMethodInjectorFactory extends SingletonMethodInjectorFactory {

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
      $hr_timestamp_builder_loader
    ); 
  }
}
