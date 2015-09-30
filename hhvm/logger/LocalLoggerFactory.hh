<?hh // strict

class LocalLoggerFactory {

  public function make(): LocalLogger {
    return new LocalLogger(new LogSerializer());
  }
}
