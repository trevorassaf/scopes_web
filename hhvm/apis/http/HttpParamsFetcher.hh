<?hh // decl 

class HttpParamsFetcher {

  public function fetch(): ImmMap<string, mixed> {
    return new ImmMap($_POST);
  }
}
