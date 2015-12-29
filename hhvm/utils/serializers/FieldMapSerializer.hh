<?hh // strict

interface FieldMapSerializer {

  public function serialize(ImmMap<string, mixed> $field_map): string;

  public function deserialize(string $field_map_string): ImmMap<string, mixed>;
}
