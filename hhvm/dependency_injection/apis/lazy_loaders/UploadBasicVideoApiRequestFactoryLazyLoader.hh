<?hh // strict

class UploadBasicVideoApiRequestFactoryLazyLoader extends LazyLoader<UploadBasicVideoApiRequestFactory> {

  public function __construct(
    private LazyLoader<HRTimeSerializer> $timeSerializerLazyLoader
  ) {}

  protected function make(): UploadBasicVideoApiRequestFactory {
    return new UploadBasicVideoApiRequestFactory($this->timeSerializerLazyLoader->load());
  }
}
