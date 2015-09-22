<?hh // strict

interface VectorRequestFieldConstraint {

  public function apply<T>(string $key, ImmVector<T> $vector): void;
}
