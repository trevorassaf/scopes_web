<?hh // strict

class Time {

  const string FORMAT = "H:i:s";

  public function isValid(string $time): bool {
    // TODO write validation logic
    return true;
  }

  public function __construct(
    private string $time
  ) {}

  public function toString(): string {
    return $this->time;
  }
}
