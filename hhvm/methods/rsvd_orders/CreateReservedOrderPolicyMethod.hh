<?hh // strict

class CreateReservedOrderPolicyMethod {

  public function __construct(
    private InsertReservedOrderPolicyQuery $insertReservedOrderQuery,
    private FetchSingletonQuery<ReservedOrderPolicy> $fetchReservedOrderPolicyQuery
  ) {}

  public function create(UnsignedInt $scopes_count): ReservedOrderPolicy {
    try {
      return $this->insertReservedOrderQuery
        ->insert($scopes_count)
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {
      throw new MethodException();
    } 
  }
}
