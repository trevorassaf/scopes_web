<?hh // strict

class CompletedBasicVideoSetFactory extends ConcreteModelFactory<CompletedBasicVideoSet> {

  public function __construct(
    private CompletedBasicVideoSetTable $table
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): CompletedBasicVideoSet {
    return new CompletedBasicVideoSet(
      $id,
      new UnsignedInt((int)$params[$this->table->getCompletedOrderIdKey()])
    );
  }
}
