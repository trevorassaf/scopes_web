<?hh // strict

class ApplicationSerializerFactory implements SerializerFactory {

  public function get(): Serializer {
    return new JsonSerializer();
  }
}
