<?hh // strict

class ObjectVectorApiRequestFieldFactory<T> {

  public function __construct(
    private ImmVector<VectorRequestFieldConstraint> $vectorRequestFieldConstraintList,
    private RequestFactory<T> $requestFactory 
  ) {}

  public function make(string $key, mixed $value): ObjectVectorApiRequestField<T> {
    // Ensure that value is array type
    if (!is_array($value)) {
      throw new RequestFieldTypeConversionException(
        RequestFieldType::VECTOR,
        $key,
        $value
      ); 
    }

    $vector = Vector{};
    foreach ($value as $element_key => $element) {
      // Ensure element is array type
      if (!is_array($element)) {
        throw new RequestFieldTypeConversionException(
          RequestFieldType::OBJECT_VECTOR,
          $element_key,
          $element
        );
      }
      $vector[] = $this->requestFactory->make(new ImmMap($element));
    }

    return new ObjectVectorApiRequestField(
      $key,
      $vector->toImmVector(),
      $this->vectorRequestFieldConstraintList
    );
  }
}
