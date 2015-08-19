<?hh //strict

abstract class Table<T> {

  const string ID_KEY = "id";

  public function getIdKey(): string {
    return self::ID_KEY; 
  }

  public function extrude(
    ImmMap<string, mixed> $param_map
  ): T {
    return $this->extrudeWithId(
      new UnsignedInt((int)$param_map[$this->getIdKey()]),
      $param_map
    );
  }
  
  abstract public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $param_map
  ): T;

  abstract public function getTableName(): string;
}
