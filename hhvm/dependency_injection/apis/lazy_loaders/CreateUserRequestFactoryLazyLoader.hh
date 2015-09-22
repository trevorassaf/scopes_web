<?hh // strict

class CreateUserRequestFactoryLazyLoader extends LazyLoader<CreateUserRequestFactory> {

  protected function make(): CreateUserRequestFactory {
    return new CreateUserRequestFactory();
  }
}
