<?hh // strict

interface ApiResultSerializer {

  public function serialize(ApiResult $result): string;
}
