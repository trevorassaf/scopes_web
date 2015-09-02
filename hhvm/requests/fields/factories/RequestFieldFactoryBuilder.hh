<?hh // strict

class RequestFieldFactoryBuilder<Ttype> {

  private Vector<RequestFieldConstraint<Ttype>> $requestFieldConstraints;

  public function __construct(
    private RequestFieldTypeConverter<Ttype> $requestFieldTypeConverter
  ) {}

  public function addConstraint(RequestFieldConstraint<Ttype> $constraint): this {
    $this->requestFieldConstraints[] = $constraint;
    return $this;
  }

  public function build(): RequestFieldFactory<Ttype> {
    return new RequestFieldFactory<Ttype>(
      new RequestFieldValidator(
        $this->requestFieldTypeConverter,
        $this->requestFieldConstraints->toImmVector()
      )
    );
  }
}
