<?hh // strict

interface SerializerFactory {

  public function get(): Serializer;
}
