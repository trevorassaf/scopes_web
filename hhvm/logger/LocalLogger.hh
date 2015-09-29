<?hh // strict

class LocalLogger extends Logger {

  protected function log(string $str): void {
    error_log($str);
  }
}
