<?hh // strict

class UpdateConfirmedOrderRequestFactoryLazyLoader extends LazyLoader<RequestFactory<UpdateConfirmedOrderRequest>> {

  protected function make(): UpdateConfirmedOrderRequestFactory {
    return new UpdateConfirmedOrderRequestFactory();
  }
}
