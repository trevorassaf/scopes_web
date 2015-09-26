<?hh // strict

class DeleteCellLabelRequestFactoryLazyLoader extends LazyLoader<RequestFactory<DeleteCellLabelRequest>> {

  protected function make(): DeleteCellLabelRequestFactory {
    return new DeleteCellLabelRequestFactory();
  }
}
