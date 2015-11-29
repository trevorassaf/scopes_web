<?hh // strict

class VectorApiRequestField<Tvalue> {
  
  public function __construct(
    private string $key,
    private ImmVector<Tvalue> $vector,
    private ImmVector<VectorRequestFieldConstraint> $constraintList
  ) {
    // Apply vector constraints
    foreach ($this->constraintList as $constraint) {
      $constraint->apply($this->key, $this->vector);
    } 
  }

  public function get(): ImmVector<Tvalue> {
    return $this->vector;
  }
}
