<?hh // strict

class MapRequestFieldFactory implements RequestFieldTypeConverter<ImmMap<string, mixed>> {

  public function convert(string $key, mixed $value): ImmMap<string, mixed> {
    
    // Validate map value
    if (!is_array($value)) {
      throw new RequestFieldTypeConversionException(
        RequestFieldType::MAP,
        $key,
        $value
      );
    }

    // Convert to map
    return new ImmMap($value);
  }
}
