<?hh // strict

class MarkBasicVideoDownloadedApiRequestFactory implements RequestFactory<MarkBasicVideoDownloadedApiRequest> {

  private RequestFieldFactory<UnsignedInt> $basicVideoIdFactory; 

  public function __construct() {
    // Unsigned int field
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $this->basicVideoIdFactory = $uint_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_fields): MarkBasicVideoDownloadedApiRequest {
    $request_builder = new MarkBasicVideoDownloadedApiRequestBuilder();
    foreach ($raw_fields as $key => $value) {
      switch ($key) {
        case MarkBasicVideoDownloadedApiRequest::BASIC_VIDEO_ID_KEY:
          $request_builder->setBasicVideoId(
            $this->basicVideoIdFactory->make($key, $value)
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
