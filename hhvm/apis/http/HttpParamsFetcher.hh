<?hh // decl 

class HttpParamsFetcher {

  public function fetch(): ImmMap<string, mixed> {
    DLogger::log("Post params", $_POST);
    return new ImmMap($_POST);
  }
}
