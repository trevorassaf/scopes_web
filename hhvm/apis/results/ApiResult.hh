<?hh // strict

interface ApiResult {
  
  public function toResponseFieldMap(): ImmMap<string, mixed>;

}
