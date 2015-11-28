<?hh // strict

class BasicVideoApiRequestFactory implements RequestFactory<BasicVideoApiRequest> {

  const int TITLE_MAX_LENGTH = 40;
  const int FILE_NAME_MAX_LENGTH = 40;
  const int DESCRIPTION_MAX_LENGTH = 200;

  private RequestFieldFactory<string> $titleFieldFactory;
  private RequestFieldFactory<Time> $videoDurationFieldFactory;
  private RequestFieldFactory<string> $fileNameFieldFactory;
  private RequestFieldFactory<string> $descriptionFieldFactory;

  public function __construct(
    TimeSerializer $time_serializer
  ) {
    // String factory builder
    $string_field_factory_builder = new StringRequestFieldFactoryBuilder();    

    $this->titleFieldFactory = $string_field_factory_builder->build();
    $this->fileNameFieldFactory = $string_field_factory_builder->build();
    $this->descriptionFieldFactory = $string_field_factory_builder->build();

    $time_request_factory_builder = new TimeRequestFieldFactoryBuilder(
      $time_serializer
    );
    $this->videoDurationFieldFactory = $time_request_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_fields): BasicVideoApiRequest {
    $request_builder = new BasicVideoApiRequestBuilder();    

    foreach ($raw_fields as $key => $value) {
      switch ($key) {
        case BasicVideoApiRequest::TITLE_KEY:
          $request_builder->setTitle(
            $this->titleFieldFactory->make($key, $value)
          );
          break;
        case BasicVideoApiRequest::VIDEO_DURATION_KEY:
          $request_builder->setVideoDuration(
            $this->videoDurationFieldFactory->make($key, $value)
          );
          break;
        case BasicVideoApiRequest::FILE_NAME_KEY:
          $request_builder->setFileName(
            $this->fileNameFieldFactory->make($key, $value)
          );
          break;
        case BasicVideoApiRequest::DESCRIPTION_KEY:
          $request_builder->setDescription(
            $this->descriptionFieldFactory->make($key, $value)
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
