<?hh // strict

class ApiResult {

  public function __construct(
    public bool $isSuccessful,
    public ApiType $apiType
  ) {}
}
