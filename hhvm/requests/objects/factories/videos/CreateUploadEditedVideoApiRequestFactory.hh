<?hh // strict

class CreateUploadEditedVideoApiRequestFactory implements RequestFactory<CreateUploadEditedVideoApiRequest> {

  const int TITLE_MAX_LENGTH_KEY = 10;
  const int DESCRIPTION_MAX_LENGTH_KEY = 100;

  private RequestFieldFactory<UnsignedInt> $userIdFieldFactory;
  private RequestFieldFactory<UnsignedInt> $editedVideoOrderIdFieldFactory;
  private RequestFieldFactory<Time> $videoDurationFieldFactory;
  private RequestFieldFactory<string> $titleFieldFactory;
  private RequestFieldFactory<string> $descriptionFieldFactory;
  private RequestFieldFactory<Timestamp> $expirationTimeFieldFactory;

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
    $this->descriptionFieldFactory = $string_field_factory_builder
      ->addConstraint(new MaxLengthConstraint(self::DESCRIPTION_MAX_LENGTH_KEY))
      ->build();

    // Duration factories
    $this->videoDurationFieldFactory = $this->timeRequestFieldFactoryBuilder->build() ;

    // Expiration time factory
    $this->expirationTimeFieldFactory = $this->timestampRequestFieldFactoryBuilder->build();
  }

  public function make(ImmMap<string, mixed> $raw_field_map): CreateUploadEditedVideoApiRequest {
    $request_builder = new CreateUploadEditedVideoApiRequestBuilder();
    foreach ($raw_field_map as $key => $value) {
      switch ($key) {
        case CreateUploadEditedVideoApiRequest::USER_ID_KEY:
          $request_builder->setUserId(
            $this->userIdFieldFactory->make($key, $value)
          );
          break;
        case CreateUploadEditedVideoApiRequest::EDITED_VIDEO_ORDER_ID_KEY:
          $request_builder->setEditedVideoOrderId(
            $this->editedVideoOrderIdFieldFactory->make($key, $value)
          );
          break;
        case CreateUploadEditedVideoApiRequest::VIDEO_DURATION_KEY:
          $request_builder->setVideoDuration(
            $this->videoDurationFieldFactory->make($key, $value)
          );
          break;
        case CreateUploadEditedVideoApiRequest::TITLE_KEY:
          $request_builder->setTitle(
            $this->titleFieldFactory->make($key, $value)
          );
          break;
        case CreateUploadEditedVideoApiRequest::DESCRIPTION_KEY:
          $request_builder->setDescription(
            $this->descriptionFieldFactory->make($key, $value)
          );
          break;
        case CreateUploadEditedVideoApiRequest::EXPIRATION_TIME_KEY:
          $request_builder->setExpirationTime(
            $this->expirationTimeFieldFactory->make($key, $value)
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
