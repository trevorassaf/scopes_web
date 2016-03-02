<?hh // strict

class ProductionApiInjectorFactory implements ApiInjectorFactory {

  private ?ApiInjector $productionApiInjector;

  public function __construct(
    private Logger $logger
  ) {}

  public function get(): ApiInjector {
    if ($this->productionApiInjector === null) {
      //// Initialize all dependencies ////
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

      // Initialize method injector
      $method_injector_factory = new ProductionMethodInjectorFactory($this->logger);
      $method_injector = $method_injector_factory->get();

      // Create api injector
      $this->productionApiInjector = new ApiInjector(
        $method_injector,
        $this->logger,
        new HttpUploadedFilesFetcher(),
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
        new UploadEditedVideoApiRequestFactoryLazyLoader(
          $timestamp_request_field_factory_builder_lazy_loader,
          $time_request_field_factory_builder_lazy_loader
        ),
        new CompleteOrderApiRequestFactoryLazyLoader(),
        $hr_timestamp_serializer_lazy_loader,
        $timestamp_builder_lazy_loader,
        $timestamp_segment_factory_lazy_loader,
        new GetAllUsersApiRequestFactoryLazyLoader(),
        new GetUsersReservedOrdersApiRequestFactoryLazyLoader(),
        new GetUsersCompletedOrdersApiRequestFactoryLazyLoader(),
        new UploadBasicVideoApiRequestFactoryLazyLoader(
          $hr_time_serializer_lazy_loader
        ),
        new MarkBasicVideoDownloadedApiRequestLazyLoader(),
        new DeleteBasicVideoApiRequestFactoryLazyLoader(),
        new GetSessionInfoApiRequestFactoryLazyLoader(),
        new GetOrderPricePolicyApiRequestFactoryLazyLoader()
      ); 
    }
    return $this->productionApiInjector;  
  }
}
