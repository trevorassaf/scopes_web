<?hh // strict

class EditedVideoOrderModelFactoryLazyLoader extends LazyLoader<ConcreteModelFactory<EditedVideoOrder>> {

  public function __construct(
    private EditedVideoOrderTableLazyLoader $editedVideoOrderTableLazyLoader,
  ) {}

  protected function make(): ConcreteModelFactory<EditedVideoOrder> {
    return new EditedVideoOrderFactory(
      $this->editedVideoOrderTableLazyLoader->load()
    );
  }
}
