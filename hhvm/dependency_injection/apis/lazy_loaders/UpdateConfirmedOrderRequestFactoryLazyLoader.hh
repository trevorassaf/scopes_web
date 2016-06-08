<?hh // strict

class UpdateConfirmedOrderApiRequestFactoryLazyLoader extends LazyLoader<RequestFactory<UpdateConfirmedOrderApiRequest>> {

  protected function make(): UpdateConfirmedOrderApiRequestFactory {
    return new UpdateConfirmedOrderApiRequestFactory();
  }
}
