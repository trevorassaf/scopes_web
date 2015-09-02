<?hh // decl 

class HttpParamsFetcher {

  public function fetch(): ImmMap<string, mixed> {
    return $_POST;
  }
}
