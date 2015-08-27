<?hh // strict

interface RequestFieldConstraint<Ttype> {

  public function apply(string $key, Ttype $value): void;
}
