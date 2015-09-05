<?hh // strict

class IsValidReservedOrderMethod {

  public function __construct(
    private IsConflictingReservedOrderMethod $isConflictingReservedOrderMethod,
  ) {}
}
