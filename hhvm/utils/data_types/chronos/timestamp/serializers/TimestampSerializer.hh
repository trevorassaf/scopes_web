<?hh // strict

interface TimestampSerializer {

  public function serialize(Timestamp $time): string;
  public function deserialize(string $timestamp_str): Timestamp;
  public function isValidString(string $timestamp_str): bool;
  public function getFormat(): string;
}
