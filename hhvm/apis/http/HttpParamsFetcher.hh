<?hh // decl 

class HttpParamsFetcher {

  public function fetch(): ImmMap<string, mixed> {
    DLogger::log("Post params", $_POST);
    DLogger::log("File params", $_FILES);
    return new ImmMap($_POST);
  }
}
