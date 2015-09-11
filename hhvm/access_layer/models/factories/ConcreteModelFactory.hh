<?hh // strict

abstract class ConcreteModelFactory<Tmodel> implements ModelFactory<Tmodel> {

  const string ID_KEY = "id";

  public function extrude(ImmMap<string, mixed> $param_map): Tmodel {
    return $this->extrudeWithId(
      new UnsignedInt((int)$param_map[$this->getIdKey()]),
      $param_map
    );
  }

  public function getIdKey(): string {
    return self::ID_KEY;
  }

  abstract public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $param_map
  ): Tmodel;
}
