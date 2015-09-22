<?hh // strict

class GetUserByEmailRequestFactoryLazyLoader extends LazyLoader<GetUserByEmailRequestFactory> {

  public function __construct(
    private LazyLoader<RequestFieldFactory<Email>> $emailFieldFactoryLoader
  ) {}

  protected function make(): GetUserByEmailRequestFactory {
    return new GetUserByEmailRequestFactory(
      $this->emailFieldFactoryLoader->load()
    );
  }
}
