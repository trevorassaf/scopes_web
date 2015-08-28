<?hh // strict

class EmptyApiResult implements ApiResult {
  
  public function toResponseFieldMap(): ImmMap<string, mixed> {
    return ImmMap{};
  }

}
