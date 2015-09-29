<?hh // strict

class LogSerializer {

  private static ImmMap<LogLevelType, string> $LOG_LEVEL_STRING_MAP = ImmMap{
    LogLevelType::DEBUG => "Debug",
    LogLevelType::INFO => "Info",
    LogLevelType::ERROR => "Error",
  };

  public function serialize(LogLevelType $level, string $str): string {
    return "Logger::[" . self::$LOG_LEVEL_STRING_MAP[$level] . "]:: " . $str; 
  }

  public function serializeObject(LogLevelType $level, mixed $object): string {
    ob_start();
    var_dump($object); 
    $contents = ob_get_contents();
    ob_end_clean();

    return $this->serialize($level, $contents);
  }
}
