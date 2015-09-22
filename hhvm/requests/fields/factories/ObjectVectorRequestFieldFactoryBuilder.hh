<?hh // strict

class ObjectVectorRequestFieldFactoryBuilder<T> {

  private Vector<VectorRequestFieldConstraint> $vectorRequestFieldConstraintList;

  public function __construct(
    private RequestFactory<T> $requestFactory
  ) {
    $this->vectorRequestFieldConstraintList = Vector{};
  }

  public function addConstraint(VectorRequestFieldConstraint $constraint): this {
    $this->vectorRequestFieldConstraintList[] = $constraint;
    return $this;
  }

  public function build(): ObjectVectorRequestFieldFactory<T> {
    return new ObjectVectorRequestFieldFactory(
      $this->vectorRequestFieldConstraintList->toImmVector(),
      $this->requestFactory
    );    
  }
}
