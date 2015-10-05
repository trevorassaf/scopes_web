<?hh // strict

interface FieldMapSerializer {

  public function serialize(ImmMap<string, mixed> $field_map): string;
}
