<?hh // strict

class UpdateCellLabelRequestFactoryLazyLoader extends LazyLoader<RequestFactory<UpdateCellLabelRequest>> {

  protected function make(): UpdateCellLabelRequestFactory {
    return new UpdateCellLabelRequestFactory(); 
  }
}
