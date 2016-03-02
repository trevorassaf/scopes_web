<?hh // strict

class GetOrderPricePolicyApiRequestFactoryLazyLoader extends LazyLoader<RequestFactory<GetOrderPricePolicyApiRequest>> {

  protected function make(): RequestFactory<GetOrderPricePolicyApiRequest> {
    return new GetOrderPricePolicyApiRequestFactory();
  }
}
