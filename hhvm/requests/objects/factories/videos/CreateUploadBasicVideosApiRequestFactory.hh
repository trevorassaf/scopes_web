<?hh // strict

class CreateUploadBasicVideosApiRequestFactory implements RequestFactory<CreateUploadBasicVideosApiRequest> {

  private RequestFieldFactory<UnsignedInt> $userIdFieldFactory;
  private RequestFieldFactory<UnsignedInt> $completedOrderIdFactory;
  private VectorApiRequestFieldFactory<BasicVideoApiRequest> $videoVectorFactory;
  
  public function __construct(
    private TimestampRequestFieldFactoryBuilder $timestampRequestFieldFactoryBuilder,
    private TimeRequestFieldFactoryBuilder $timeRequestFieldFactoryBuilder,
    private TimeSerializer $timeSerializer
  ) {
    // UnsignedInt factories
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $this->userIdFieldFactory = $uint_field_factory_builder->build();
    $this->completedOrderIdFactory = $uint_field_factory_builder->build();

    // Video map factory
    $string_field_factory_builder = new StringRequestFieldFactoryBuilder();
    $basic_video_api_request_factory = new BasicVideoApiRequestFactory(
      $this->timeSerializer
    );
    $this->videoVectorFactory = new VectorApiRequestFieldFactory(
      $basic_video_api_request_factory
    );
  }

  public function make(ImmMap<string, mixed> $raw_field_map): CreateUploadBasicVideosApiRequest {
    $request_builder = new CreateUploadBasicVideosApiRequestBuilder(); 
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case CreateUploadBasicVideosApiRequest::USER_ID_KEY:
          $request_builder->setUserId(
            $this->userIdFieldFactory->make($key, $value)
          );
          break;
        case CreateUploadBasicVideosApiRequest::COMPLETED_ORDER_ID_KEY:
          $request_builder->setCompletedOrderId(
            $this->completedOrderIdFactory->make($key, $value)
          );
          break;
        case CreateUploadBasicVideosApiRequest::VIDEO_MAP_KEY:
          $request_builder->setBasicVideos(
            $this->videoVectorFactory->convert(
              $key,
              $value
            )
          );
          break;
        default:
          throw new UnexpectedRequestFieldKeyException(__CLASS__, $key);
          break;
      }
    }
    return $request_builder->build();
  }
}
