<?hh // strict

class ConfirmOrderApiRequestFactoryLazyLoader extends LazyLoader<ConfirmOrderApiRequestFactory> {

  protected function make(): ConfirmOrderApiRequestFactory {
    return new ConfirmOrderApiRequestFactory();    
  }
}
