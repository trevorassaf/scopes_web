<?hh // strict

class DeleteBasicVideoApiRequestFactoryLazyLoader extends LazyLoader<RequestFactory<DeleteBasicVideoApiRequest>> {

  protected function make(): RequestFactory<DeleteBasicVideoApiRequest> {
    return new DeleteBasicVideoApiRequestFactory();
  }
}
