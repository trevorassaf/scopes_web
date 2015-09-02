<?hh // strict

interface ApiRequestDeserializer {

  public function deserialize(string $payload): ImmMap<string, mixed>;
}
