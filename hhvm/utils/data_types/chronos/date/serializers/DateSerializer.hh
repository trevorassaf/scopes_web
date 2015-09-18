<?hh // strict

interface DateSerializer {

  public function serialize(Date $date): string;

  public function deserialize(string $date_str): Date;

  public function isValidString(string $date_str): bool;
}
