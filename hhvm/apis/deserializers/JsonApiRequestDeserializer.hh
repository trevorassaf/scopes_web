<?hh // strict

class JsonApiRequestDeserializer implements ApiRequestDeserializer {

  public function deserialize(string $payload): ImmMap<string, mixed> {
    $json_object = json_decode($payload, true); 
    if ($json_object == false) {
      throw new MalformedApiRequestException();
    }
    return new ImmMap($json_object);
  }
}
