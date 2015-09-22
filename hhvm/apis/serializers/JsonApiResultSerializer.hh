<?hh // strict

class JsonApiResultSerializer implements ApiResultSerializer {

  public function serialize(ApiResult $result): string {
    return json_encode($result, true);
  }
}
