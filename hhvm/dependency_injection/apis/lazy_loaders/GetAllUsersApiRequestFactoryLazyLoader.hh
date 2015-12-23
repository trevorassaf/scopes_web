<?hh // strict

class GetAllUsersApiRequestFactoryLazyLoader extends LazyLoader<RequestFactory<GetAllUsersApiRequest>> {

  protected function make(): RequestFactory<GetAllUsersApiRequest> {
    return new GetAllUsersRequestFactory();
  }

}
