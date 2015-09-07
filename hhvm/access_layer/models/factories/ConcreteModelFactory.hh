<?hh // strict

abstract class ConcreteModelFactory<Tmodel> implements ModelFactory<Tmodel> {

  public function extrude(ImmMap<string, mixed> $param_map): Tmodel {
    return $this->extrudeWithId(
      new UnsignedInt((int)$param_map[$this->getIdKey()]),
      $param_map
    );
  }

  abstract public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $param_map
  ): Tmodel;
}
