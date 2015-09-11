<?hh // strict

interface FetchQueryMaker<Tmodel> {

  public function serialize(): string;

//  public function extrude(ImmMap<string, mixed> $field_map): Tmodel;
}
