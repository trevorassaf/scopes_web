<?hh // strict

class GetUserByEmailRequestFactoryLazyLoader extends LazyLoader<GetUserByEmailRequestFactory> {

  protected function make(): GetUserByEmailRequestFactory {
    $email_field_factory_builder = new EmailRequestFieldFactoryBuilder();
    return new GetUserByEmailRequestFactory(
      $email_field_factory_builder->build()
    );
  }
}
