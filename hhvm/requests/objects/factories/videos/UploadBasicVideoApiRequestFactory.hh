<?hh // strict

class UploadBasicVideoApiRequestFactory implements RequestFactory<UploadBasicVideoApiRequest> {

  const int TITLE_MAX_LENGTH = 40;
  const int FILE_NAME_MAX_LENGTH = 40;
  const int DESCRIPTION_MAX_LENGTH = 200;

  private RequestFieldFactory<UnsignedInt> $completedOrderIdFactory;
  private RequestFieldFactory<UnsignedInt> $scopeIndexFactory;
  private RequestFieldFactory<string> $titleFieldFactory;
  private RequestFieldFactory<Time> $videoDurationFieldFactory;
  private RequestFieldFactory<string> $fileNameFieldFactory;
  private RequestFieldFactory<string> $descriptionFieldFactory;

  public function __construct(
    TimeSerializer $time_serializer
  ) {
    // Unsigned int fields 
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $this->completedOrderIdFactory = $uint_field_factory_builder->build();
    $this->scopeIndexFactory = $uint_field_factory_builder->build();

    // String fields 
    $string_field_factory_builder = new StringRequestFieldFactoryBuilder();    

    $this->titleFieldFactory = $string_field_factory_builder->build();
    $this->fileNameFieldFactory = $string_field_factory_builder->build();
    $this->descriptionFieldFactory = $string_field_factory_builder->build();

    // Time fields
    $time_request_factory_builder = new TimeRequestFieldFactoryBuilder(
      $time_serializer
    );
    $this->videoDurationFieldFactory = $time_request_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_fields): UploadBasicVideoApiRequest {
    $request_builder = new UploadBasicVideoApiRequestBuilder();    

    foreach ($raw_fields as $key => $value) {
      switch ($key) {
      case UploadBasicVideoApiRequest::COMPLETED_ORDER_ID_KEY:
        $request_builder->setCompletedOrderId(
          $this->completedOrderIdFactory->make($key, $value)
        );
        break;
      case UploadBasicVideoApiRequest::SCOPE_INDEX_KEY:
        $request_builder->setScopeIndex(
          $this->scopeIndexFactory->make($key, $value)
        );
        break;
      case UploadBasicVideoApiRequest::TITLE_KEY:
        $request_builder->setTitle(
          $this->titleFieldFactory->make($key, $value)
        );
        break;
      case UploadBasicVideoApiRequest::VIDEO_DURATION_KEY:
        $request_builder->setVideoDuration(
          $this->videoDurationFieldFactory->make($key, $value)
        );
        break;
      case UploadBasicVideoApiRequest::FILE_NAME_KEY:
        $request_builder->setFileName(
          $this->fileNameFieldFactory->make($key, $value)
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
