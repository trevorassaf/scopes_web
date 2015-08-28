<?hh // strict

class HttpParamsFetcher {

  public function fetch(): ImmMap<string, mixed> {
    return $_POST;
  }
}
