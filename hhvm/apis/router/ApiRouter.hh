<?hh // strict

interface ApiRouter {

  public function route(
    ApiType $type,
    UserAgent $user_agent,
    ImmMap<string, mixed> $raw_request_fields
  ): ApiResult;
}
