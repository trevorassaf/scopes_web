<?hh // strict

class TermBuilder {

  public function __construct(
    private ComparisonOperatorTypeStringer $comparisonOperatorTypeStringer
  ) {}
  
  public function equalTo(
    string $lhs,
    mixed $rhs
  ): Term {
    return new Term(
      $this->comparisonOperatorTypeStringer,
      $lhs,
      $rhs,
      ComparisonOperatorType::EQUAL_TO
    );
  }

  public function notEqualTo(
    string $lhs,
    mixed $rhs
  ): Term {
    return new Term(
      $this->comparisonOperatorTypeStringer,
      $lhs,
      $rhs,
      ComparisonOperatorType::NOT_EQUAL_TO
    );
  }
  
  public function greaterThan(
    string $lhs,
    mixed $rhs
  ): Term {
    return new Term(
      $this->comparisonOperatorTypeStringer,
      $lhs,
      $rhs,
      ComparisonOperatorType::GREATER_THAN
    );
  }
  
  public function greaterThanOrEqualTo(
    string $lhs,
    mixed $rhs
  ): Term {
    return new Term(
      $this->comparisonOperatorTypeStringer,
      $lhs,
      $rhs,
      ComparisonOperatorType::GREATER_THAN_OR_EQUAL_TO
    );
  }
  
  public function lessThan(
    string $lhs,
    mixed $rhs
  ): Term {
    return new Term(
      $this->comparisonOperatorTypeStringer,
      $lhs,
      $rhs,
      ComparisonOperatorType::LESS_THAN
    );
  }
  
  public function lessThanOrEqualTo(
    string $lhs,
    mixed $rhs
  ): Term {
    return new Term(
      $this->comparisonOperatorTypeStringer,
      $lhs,
      $rhs,
      ComparisonOperatorType::LESS_THAN_OR_EQUAL_TO
    );
  }
}
