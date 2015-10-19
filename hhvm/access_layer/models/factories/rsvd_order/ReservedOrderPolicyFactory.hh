<?hh // strict

class ReservedOrderPolicyFactory extends ConcreteModelFactory<ReservedOrderPolicy> {
  
  public function __construct(
    private ReservedOrderPolicyTable $table      
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): ReservedOrderPolicy {
    return new ReservedOrderPolicy(
      $id,
      new UnsignedInt((int)$params[$this->table->getScopesCountKey()])
    );
  }
}
