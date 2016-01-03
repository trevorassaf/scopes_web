<?hh // strict

class MarkBasicVideoDownloadedApiRequestLazyLoader extends LazyLoader<RequestFactory<MarkBasicVideoDownloadedApiRequest>>{

  protected function make(): RequestFactory<MarkBasicVideoDownloadedApiRequest> {
    return new MarkBasicVideoDownloadedApiRequestFactory();
  }
}
