<?hh // strict

class NullableRequestFieldFactoryBuilder<Ttype> {

  private Vector<RequestFieldConstraint<Ttype>> $requestFieldConstraints;

  public function __construct(
    private RequestFieldTypeConverter<Ttype> $requestFieldTypeConverter
  ) {
    $this->requestFieldConstraints = Vector{};
  }
  
  public function addConstraint(RequestFieldConstraint<Ttype> $constraint): this {
    $this->requestFieldConstraints[] = $constraint;
    return $this;
  }

  public function build(): NullableRequestFieldFactory<Ttype> {
    return new NullableRequestFieldFactory(
      new RequestFieldValidator(
        $this->requestFieldTypeConverter,
        $this->requestFieldConstraints->toImmVector()
      )
    );
  }
}
