<?hh // strict

class MapApiRequestField<Tkey, Tvalue> {
  
  private function __construct(
    private string $key,
    private ImmMap<Tkey, Tvalue> $map,
    private ImmVector<MapApiRequestFieldConstraint> $constraintList
  ) {
    // Apply map constraints
    foreach ($this->constraintList as $constraint) {
      $constraint->apply($this->key, $this->map);
    }
  }

  public function get(): ImmMap<Tkey, Tvalue> {
    return $this->map;
  }
}
