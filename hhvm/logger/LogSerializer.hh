<?hh // strict

class LogSerializer {

  private static ImmMap<LogLevelType, string> $LOG_LEVEL_STRING_MAP = ImmMap{
    LogLevelType::DEBUG => "Debug",
    LogLevelType::INFO => "Info",
    LogLevelType::ERROR => "Error",
  };

  public function serialize(LogLevelType $level, string $str, mixed $object=null): string {
    $log_str = "Logger::[" . self::$LOG_LEVEL_STRING_MAP[$level] . "]:: " . $str;
    if ($object !== null) {
      $log_str .= ", " . $this->serializeObject($object);
    }
    return $log_str;
  }

  private function serializeObject(mixed $object): string {
    ob_start();
    var_dump($object); 
    $contents = ob_get_contents();
    ob_end_clean();

    return $contents;
  }
}
