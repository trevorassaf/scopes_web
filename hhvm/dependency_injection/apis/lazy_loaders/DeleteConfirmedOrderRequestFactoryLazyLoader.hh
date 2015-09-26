<?hh // strict

class DeleteConfirmedOrderRequestFactoryLazyLoader extends LazyLoader<RequestFactory<DeleteConfirmedOrderRequest>> {
  
  protected function make(): DeleteConfirmedOrderRequestFactory {
    return new DeleteConfirmedOrderRequestFactory();
  }
}
