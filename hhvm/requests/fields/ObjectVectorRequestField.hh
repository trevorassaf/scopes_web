<?hh // strict

class ObjectVectorRequestField<Ttype> {


  public function __construct(
    private string $key,
    private ImmVector<Ttype> $collection,
    private ImmVector<VectorRequestFieldConstraint> $vectorRequestFieldConstraintList
  ) {
    // Apply vector constraints
    foreach ($this->vectorRequestFieldConstraintList as $vector_constraint) {
      $vector_constraint->apply($this->key, $this->collection); 
    }
  }

  public function get(): ImmVector<Ttype> {
    return $this->collection;
  }
}
