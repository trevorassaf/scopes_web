<?hh // strict

interface ModelFactory<Tmodel> {

  public function extrude(ImmMap<string, mixed> $param_map): Tmodel;

}
