<?hh // strict

abstract class Logger {

  public function __construct(
    private LogSerializer $logSerializer
  ) {}

  abstract protected function log(string $str): void;

  public function debug(string $str): void {
    $log_str = $this->logSerializer->serialize(
      LogLevelType::DEBUG,
      $str
    );
    $this->log($log_str);
  }

  public function debugObject(mixed $str): void {
    $log_str = $this->logSerializer->serializeObject(
      LogLevelType::DEBUG,
      $str
    );
    $this->log($log_str);
  }

  public function info(string $str): void {
    $log_str = $this->logSerializer->serialize(
      LogLevelType::INFO,
      $str
    );
    $this->log($log_str);
  }

  public function infoObject(mixed $str): void {
    $log_str = $this->logSerializer->serializeObject(
      LogLevelType::INFO,
      $str
    );
    $this->log($log_str);
  }
  
  public function error(string $str): void {
    $log_str = $this->logSerializer->serialize(
      LogLevelType::ERROR,
      $str
    );
    $this->log($log_str);
  }

  public function errorObject(mixed $str): void {
    $log_str = $this->logSerializer->serializeObject(
      LogLevelType::ERROR,
      $str
    );
    $this->log($log_str);
  }
}
