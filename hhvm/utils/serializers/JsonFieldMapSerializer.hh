<?hh // strict

class JsonFieldMapSerializer implements FieldMapSerializer {

  public function serialize(ImmMap<string, mixed> $field_map): string {
    $result = json_encode($field_map);
    if ($result === null) {
      throw new FailedSerializationException($field_map);
    }
    return $result;
  }  

  public function deserialize(string $serialized_field_map): ImmMap<string, mixed> {
    $result = json_decode($serialized_field_map);
    if ($result === null) {
      throw new FailedDeserializationException($serialized_field_map);
    }

    return $result;
  }
}
