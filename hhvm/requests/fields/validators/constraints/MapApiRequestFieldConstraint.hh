<?hh // strict

interface MapApiRequestFieldConstraint {

  public function apply<Tkey, Tvalue>(Tkey $key, Tvalue $value): void;
}
