<?hh // strict

class EmptyApiResult implements ApiResult {
  
  public function serialize(): string {
    return '';
  }

}
