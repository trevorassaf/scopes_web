<?hh // strict

class VectorApiRequestFieldFactory<Tvalue> implements RequestFieldTypeConverter<VectorApiRequestField<Tvalue>> {

  public function __construct(
    private RequestFactory<Tvalue> $valueFactory
  ) {}

  public function convert(string $vector_key, mixed $vector_payload): VectorApiRequestField<Tvalue> {

    // Validate vector value
    if (!is_array($vector_payload)) {
      throw new RequestFieldTypeConversionException(
        RequestFieldType::VECTOR,
        $vector_key,
        $vector_payload
      );
    }

    $processed_vector_payload = new ImmVector($vector_payload);

    // Convert "payload" to ImmVector<Tvalue>
    $vector_result = Vector{};

    foreach ($processed_vector_payload as $field_value) {
      // Check that video field is a map
      if (!is_array($field_value)) {
        throw new RequestFieldTypeConversionException(
          RequestFieldType::MAP,
          $vector_key,
          $field_value
        );
      }

      $vector_result[] = $this->valueFactory->make(
        new ImmMap($field_value)
      );
    }

    return new VectorApiRequestField(
      $vector_key,
      $vector_result->toImmVector(),
      ImmVector{}
    );
  }
}
