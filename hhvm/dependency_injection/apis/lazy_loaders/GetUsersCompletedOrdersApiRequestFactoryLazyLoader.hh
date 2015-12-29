<?hh // strict

class GetUsersCompletedOrdersApiRequestFactoryLazyLoader extends LazyLoader<RequestFactory<GetUsersCompletedOrdersApiRequest>> {

  protected function make(): RequestFactory<GetUsersCompletedOrdersApiRequest> {
    return new GetUsersCompletedOrdersApiRequestFactory();
  }
}
