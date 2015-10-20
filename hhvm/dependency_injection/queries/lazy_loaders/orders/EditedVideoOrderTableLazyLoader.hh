<?hh // strict

class EditedVideoOrderTableLazyLoader extends LazyLoader<EditedVideoOrderTable> {

  protected function make(): EditedVideoOrderTable {
    return new EditedVideoOrderTable();
  }
}
