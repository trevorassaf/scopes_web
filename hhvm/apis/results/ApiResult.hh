<?hh // strict

abstract class ApiResult {

  const string IS_SUCCESSFUL_KEY = "is_successful";
  const string API_TYPE_KEY = "api_type";

  public function __construct(
    private bool $isSuccessful,
    private ApiType $apiType
  ) {}

  public function getResultFields(): ImmMap<string, mixed> {
    $custom_result_fields = $this->getCustomResultFields()->toMap();

    // Ensure custom result fields don't contain top-level result fields
    invariant(
      $custom_result_fields->containsKey(self::IS_SUCCESSFUL_KEY),
      "ApiResult can't contain " . self::IS_SUCCESSFUL_KEY
    );

    invariant(
      $custom_result_fields->containsKey(self::API_TYPE_KEY),
      "ApiResult can't contain " . self::API_TYPE_KEY
    );

    // Add top-level result fields
    $custom_result_fields[self::IS_SUCCESSFUL_KEY] = $this->isSuccessful;
    $custom_result_fields[self::API_TYPE_KEY] = (int)$this->apiType;

    return $custom_result_fields->toImmMap();
  }

  abstract protected function getCustomResultFields(): ImmMap<string, mixed>;
}
