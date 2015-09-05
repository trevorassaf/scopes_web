<?hh // strict

abstract class ComparisonTerm implements MySqlTerm {

  public function __construct(
    private mixed $left,
    private mixed $right
  ) {} 

  public function serialize(): string {
  
  }

  abstract protected function getComparisonToken(): string; 
}
