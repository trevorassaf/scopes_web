<?hh // strict

class DeleteReservedOrderRequestFactoryLazyLoader extends LazyLoader<RequestFactory<DeleteReservedOrderRequest>> {

  protected function make(): DeleteReservedOrderRequestFactory {
    return new DeleteReservedOrderRequestFactory();
  }
}
