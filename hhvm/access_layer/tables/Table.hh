<?hh //strict

abstract class Table {

  const string ID_KEY = "id";
  const string TABLE_QUALIFYING_TOKEN = ".";

  public function getIdKey(): string {
    return $this->makeTableQualifiedKey(self::ID_KEY); 
  }

  abstract public function getName(): string;

  protected function makeTableQualifiedKey(string $key_name): string {
    return $this->getName() . self::TABLE_QUALIFYING_TOKEN . $key_name; 
  }
}
