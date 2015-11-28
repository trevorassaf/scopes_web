<?hh // strict

class ProductionApiInjectorFactory implements ApiInjectorFactory {

  private ?ApiInjector $productionApiInjector;

  public function __construct(
    private Logger $logger
  ) {}

  public function make(): ApiInjector {
    if ($this->productionApiInjector === null) {
      // Initialize all dependencies
      $production_method_injector_factory = new ProductionMethodInjectorFactory(
        $this->logger
      );

      // Chronos dependencies
      $hr_time_serializer = new HRTimeSerializer();
      $hr_time_serializer_lazy_loader = new HRTimeSerializerLazyLoader();

      $hr_timestamp_serializer = new HRTimestampSerializer(
        new HRDateSerializer(),
        $hr_time_serializer
      );

      $hr_timestamp_serializer_lazy_loader = new HRTimestampSerializerLazyLoader(
        new HRDateSerializerLazyLoader(),
        new HRTimeSerializerLazyLoader()
      );

      $timestamp_builder_lazy_loader = new TimestampBuilderLazyLoader(
        $hr_timestamp_serializer_lazy_loader
      );

      $timestamp_segment_factory_lazy_loader = new TimestampSegmentFactoryLazyLoader(
        $hr_timestamp_serializer_lazy_loader
      );

      $timestamp_request_field_factory_builder_lazy_loader = new TimestampRequestFieldFactoryBuilderLazyLoader(
        $hr_timestamp_serializer_lazy_loader
      );
      
      $time_request_field_factory_builder_lazy_loader = new TimeRequestFieldFactoryBuilderLazyLoader(
        $hr_time_serializer_lazy_loader
      );

      $this->productionApiInjector = new ApiInjector(
        $production_method_injector_factory->get(),
        $this->logger,
        new CreateUserRequestFactoryLazyLoader(), 
        new GetUserByEmailRequestFactoryLazyLoader(), 
        new ReserveOrderRequestFactoryLazyLoader(
          $hr_timestamp_serializer
        ),
        new ConfirmOrderApiRequestFactoryLazyLoader(),
        new UpdateConfirmedOrderRequestFactoryLazyLoader(),
        new UpdateCellLabelRequestFactoryLazyLoader(),
        new DeleteCellLabelRequestFactoryLazyLoader(),
        new DeleteReservedOrderRequestFactoryLazyLoader(),
        new DeleteConfirmedOrderRequestFactoryLazyLoader(),
        new GetUsersConfirmedOrdersRequestFactoryLazyLoader(),
        new CreateUploadBasicVideosApiRequestFactoryLazyLoader(
          $timestamp_request_field_factory_builder_lazy_loader,
          $time_request_field_factory_builder_lazy_loader,
          $hr_time_serializer_lazy_loader
        ),
        new CreateUploadEditedVideoApiRequestFactoryLazyLoader(
          $timestamp_request_field_factory_builder_lazy_loader,
          $time_request_field_factory_builder_lazy_loader
        ),
        $hr_timestamp_serializer_lazy_loader,
        $timestamp_builder_lazy_loader,
        $timestamp_segment_factory_lazy_loader
      ); 
    }
    return $this->productionApiInjector;  
  }
}
