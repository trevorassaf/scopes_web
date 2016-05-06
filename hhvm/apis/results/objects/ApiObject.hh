<?hh // strict

interface ApiObject {

  public function getResultFields(): ImmMap<string, mixed>;
}
