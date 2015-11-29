<?hh // strict

class MapApiRequestFieldFactory<Tkey, Tvalue> implements RequestFieldTypeConverter<MapApiRequestField<Tkey, Tvalue>> {

  public function __construct(
    private RequestFieldFactory<Tkey> $keyFieldFactory,
    private RequestFactory<Tvalue> $valueFieldFactory
  ) {}

  public function convert(string $map_key, mixed $map_payload): MapApiRequestField<Tkey, Tvalue> {

    DLogger::log($map_key, $map_payload);

    // Validate map value
    if (!is_array($map_payload)) {
      throw new RequestFieldTypeConversionException(
        RequestFieldType::MAP,
        $map_key,
        $map_payload
      );
    }

    // Convert "value" to ImmMap<Tkey, Tvalue>, and validate of course
    $map_result = Map{};
    
    foreach ($map_payload as $field_key => $field_value) {
      $processed_key = $this->keyFieldFactory->make($map_key, $field_key);
      
      if (!is_array($field_value)) {
        throw new RequestFieldTypeConversionException(
          RequestFieldType::MAP,
          $map_key,
          $field_value
        );
      }

      $field_value_map = new ImmMap($field_value);
      $processed_value = $this->valueFieldFactory->make($field_value_map);
      $map_result[$processed_key->get()] = $processed_value;
    }

    // Convert to map
    return new MapApiRequestField(
      $map_key,
      $map_result->toImmMap(),
      ImmVector{} 
    ); 
  }
}
