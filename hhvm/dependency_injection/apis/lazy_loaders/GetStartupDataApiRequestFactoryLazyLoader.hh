<?hh // strict

class GetStartupDataApiRequestFactoryLazyLoader extends LazyLoader<RequestFactory<GetStartupDataApiRequest>> {

  protected function make(): RequestFactory<GetStartupDataApiRequest> {
    return new GetStartupDataApiRequestFactory();
  }
}
