<?hh // strict

class ConfirmOrderRequestFactoryLazyLoader extends LazyLoader<ConfirmOrderRequestFactory> {

  protected function make(): ConfirmOrderRequestFactory {
    return new ConfirmOrderRequestFactory();    
  }
}
