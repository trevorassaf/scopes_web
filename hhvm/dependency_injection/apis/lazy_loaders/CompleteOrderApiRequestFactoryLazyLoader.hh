<?hh // strict

class CompleteOrderApiRequestFactoryLazyLoader extends LazyLoader<RequestFactory<CompleteOrderApiRequest>> {

  public function __construct() {}

  protected function make(): RequestFactory<CompleteOrderApiRequest> {
    return new CompleteOrderRequestFactory();  
  }
}
