<?hh // strict

interface ApiRouter {

  public function route(
    ApiType $type,
    ImmMap<string, mixed> $raw_request_fields
  ): ApiResult;
}
