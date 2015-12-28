<?hh // strict

class GetUsersReservedOrdersApiRequestFactoryLazyLoader extends LazyLoader<RequestFactory<GetUsersReservedOrdersApiRequest>> {

  protected function make(): RequestFactory<GetUsersReservedOrdersApiRequest> {
    return new GetUsersReservedOrdersApiRequestFactory();
  }
}
