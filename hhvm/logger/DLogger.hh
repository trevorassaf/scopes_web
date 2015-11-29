<?hh // strict

class DLogger {

  private static ?LocalLogger $localLogger;

  public static function log(string $message, mixed $object=null): void {
    if (self::$localLogger === null) {
      self::$localLogger = new LocalLogger(
        new LogSerializer()
      ); 
    }  
    self::$localLogger->debug($message, $object);
  }
}
