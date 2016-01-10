<?hh // strict

class UploadEditedVideoApiRequestFactory implements RequestFactory<UploadEditedVideoApiRequest> {

  const int TITLE_MAX_LENGTH_KEY = 10;
  const int DESCRIPTION_MAX_LENGTH_KEY = 100;

  private RequestFieldFactory<UnsignedInt> $userIdFieldFactory;
  private RequestFieldFactory<UnsignedInt> $editedVideoOrderIdFieldFactory;
  private RequestFieldFactory<Time> $videoDurationFieldFactory;
  private RequestFieldFactory<string> $titleFieldFactory;
  private RequestFieldFactory<string> $descriptionFieldFactory;

  public function __construct(
    private TimestampRequestFieldFactoryBuilder $timestampRequestFieldFactoryBuilder,
    private TimeRequestFieldFactoryBuilder $timeRequestFieldFactoryBuilder
  ) {
    // UnsignedInt factories
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $this->userIdFieldFactory = $uint_field_factory_builder->build();
    $this->editedVideoOrderIdFieldFactory = $uint_field_factory_builder->build(); 

    // String factories
    $string_field_factory_builder = new StringRequestFieldFactoryBuilder();
    $this->titleFieldFactory = $string_field_factory_builder
      ->addConstraint(new MaxLengthConstraint(self::TITLE_MAX_LENGTH_KEY))
      ->build();

    $description_field_factory_builder = new StringRequestFieldFactoryBuilder();
    $this->descriptionFieldFactory = $description_field_factory_builder
      ->addConstraint(new MaxLengthConstraint(self::DESCRIPTION_MAX_LENGTH_KEY))
      ->build();

    // Duration factories
    $this->videoDurationFieldFactory = $this->timeRequestFieldFactoryBuilder->build() ;
  }

  public function make(ImmMap<string, mixed> $raw_field_map): UploadEditedVideoApiRequest {
    $request_builder = new UploadEditedVideoApiRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case UploadEditedVideoApiRequest::EDITED_VIDEO_ORDER_ID_KEY:
          $request_builder->setEditedVideoOrderId(
            $this->editedVideoOrderIdFieldFactory->make($key, $value)
          );
          break;
        case UploadEditedVideoApiRequest::VIDEO_DURATION_KEY:
          $request_builder->setVideoDuration(
            $this->videoDurationFieldFactory->make($key, $value)
          );
          break;
        case UploadEditedVideoApiRequest::TITLE_KEY:
          $request_builder->setTitle(
            $this->titleFieldFactory->make($key, $value)
          );
          break;
        case UploadEditedVideoApiRequest::DESCRIPTION_KEY:
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
