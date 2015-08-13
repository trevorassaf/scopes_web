<?hh // decl 

class WebParamsFetcher {

  public function fetchGetParam(string $key): string {
    if (!$this->fetchGetParam($key)) {
      throw new ApiException(
        "Malformed api request: " . $key . " GET param is not set!"
      ); 
    }
  }

  public function isGetParamSet(string $key): bool {
    return isset($_GET[$key]);
  }
  
  public function fetchPostParam(string $key): string {
    if (!$this->fetchPostParam($key)) {
      throw new ApiException(
        "Malformed api request: " . $key . " POST param is not set!"
      ); 
    }
  }

  public function isPostParamSet(string $key): bool {
    return isset($_POST[$key]);
  }
}
