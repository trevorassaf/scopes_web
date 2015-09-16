<?hh // strict

interface TimeSerializer {

  public function serialize(Time $time): string;
  public function deserialize(string $time_str): Time;
  public function isValidString(string $time_str): bool;
}
