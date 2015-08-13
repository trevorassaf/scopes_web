<?hh // strict

interface Serializer {

  public function serialize(): string;
  
  public function addParameter(
    string $key,
    mixed $value
  ): this;

}
