<?hh // strict

class JsonSerializer implements Serializer {

  private Map<string, mixed> $parameters;

  public function __construct() {
    $this->parameters = Map{};
  }

  public function serialize(): string {
    return json_encode($this->parameters->toArray());
  }

  public function addParameter(
    string $key,
    mixed $value 
  ): this {
    $this->parameters[$key] = $value;
    return $this;
  }
}
