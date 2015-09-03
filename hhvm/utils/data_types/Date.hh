<?hh // strict

class Date {

  const string FORMAT = "Y-m-d";

  public static function isValid(string $date): bool {
    // TODO write validation logic
    return true;
  }

  public function __construct(
    private string $date    
  ) {}

  public function toString(): string {
    return $this->date;
  }
}
