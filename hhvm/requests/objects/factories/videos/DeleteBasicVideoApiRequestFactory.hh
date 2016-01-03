<?hh // strict

class DeleteBasicVideoApiRequestFactory {

  private RequestFieldFactory<UnsignedInt> $basicVideoIdFactory;
  private RequestFieldFactory<bool> $blockIfNotDownloadedFactory;

  public function __construct() {
    // Unsigned int field
    $uint_field_factory_builder = new UnsignedIntRequestFieldFactoryBuilder();
    $this->basicVideoIdFactory = $uint_field_factory_builder->build();

    // Bool field
    $bool_field_factory_builder = new BoolRequestFieldFactoryBuilder();
    $this->blockIfNotDownloadedFactory = $bool_field_factory_builder->build();
  }

  public function make(ImmMap<string, mixed> $raw_fields): DeleteBasicVideoApiRequest {
    $request_builder = new DeleteBasicVideoApiRequestBuilder();
    foreach ($raw_fields as $key => $value) {
      switch ($key) {
        case DeleteBasicVideoApiRequest::BASIC_VIDEO_ID_KEY:
          $request_builder->setVideoId(
            $this->basicVideoIdFactory->make($key, $value)
          );
          break;
        case DeleteBasicVideoApiRequest::BLOCK_IF_NOT_DOWNLOADED_KEY:
          $request_builder->setBlockIfNotDownloaded(
            $this->blockIfNotDownloadedFactory->make($key, $value)
          );
          break;
      }
    }
    return $request_builder->build();
  }

}
