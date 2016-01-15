<?hh // strict

class GetSessionInfoApiRequestFactoryLazyLoader extends LazyLoader<RequestFactory<GetSessionInfoApiRequest>> {

  protected function make(): GetSessionInfoApiRequestFactory {
    return new GetSessionInfoApiRequestFactory();
  }
}
