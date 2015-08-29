<?hh // strict

class TypedApiResult extends ApiResult {

  public function __construct(
    public bool $isSuccessful
  ) {}
}
