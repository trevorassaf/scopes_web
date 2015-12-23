<?hh // strict

class CompleteOrderApiRequestFactoryLazyLoader extends LazyLoader<RequestFactory<CompleteOrderApiRequest>> {

  protected function make(): RequestFactory<CompleteOrderApiRequest> {
    return new CompleteOrderRequestFactory();  
  }
}
