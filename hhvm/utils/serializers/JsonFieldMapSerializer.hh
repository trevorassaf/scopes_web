<?hh // strict

class JsonFieldMapSerializer implements FieldMapSerializer {

  public function serialize(ImmMap<string, mixed> $field_map): string {
    return json_encode($field_map);
  }  
}
