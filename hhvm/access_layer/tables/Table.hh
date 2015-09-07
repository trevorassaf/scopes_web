<?hh //strict

abstract class Table<T> {

  const string ID_KEY = "id";
  const string TABLE_QUALIFYING_TOKEN = ".";

  public function getIdKey(): string {
    return self::ID_KEY; 
  }

  abstract public function getTableName(): string;

  protected function makeTableQualifiedKey(string $key_name): string {
    return $this->getTableName() . self::TABLE_QUALIFYING_TOKEN . $key_name; 
  }
}
