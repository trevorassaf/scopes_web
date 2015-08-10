<?hh // strict

interface Table<T as Model> {

  public function fetchById(UnsignedInt $id): T;
  public function fetchAll(): ImmVector<T>;
  public function insert(T $model): void;
  public function deleteById(UnsignedInt $id): void;
  public function deleteAll(): void;
}
