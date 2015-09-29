<?hh // strict

abstract class Logger {

  public function __construct(
    private LogSerializer $logSerializer
  ) {}

  abstract protected function log(string $str): void;

  public function debug(string $str, mixed $object=null): void {
    $log_str = $this->logSerializer->serialize(
      LogLevelType::DEBUG,
      $str,
      $object
    );
    $this->log($log_str);
  }

  public function info(string $str, mixed $object=null): void {
    $log_str = $this->logSerializer->serialize(
      LogLevelType::INFO,
      $str,
      $object
    );
    $this->log($log_str);
  }
  
  public function error(string $str, mixed $object=null): void {
    $log_str = $this->logSerializer->serialize(
      LogLevelType::ERROR,
      $str,
      $object
    );
    $this->log($log_str);
  }
}
