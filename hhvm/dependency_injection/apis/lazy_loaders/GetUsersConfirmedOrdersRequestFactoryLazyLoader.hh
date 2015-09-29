<?hh // strict

class GetUsersConfirmedOrdersRequestFactoryLazyLoader extends LazyLoader<GetUsersConfirmedOrdersRequestFactory> {

  protected function make(): GetUsersConfirmedOrdersRequestFactory {
    return new GetUsersConfirmedOrdersRequestFactory();    
  }
}
