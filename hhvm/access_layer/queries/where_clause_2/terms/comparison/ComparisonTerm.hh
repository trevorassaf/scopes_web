<?hh // strict

abstract class ComparisonTerm implements MySqlTerm {

  public function __construct(
    private string $left,
    private string $right
  ) {} 

  public function serialize(): string {
    return "(" . $this->left . " " . $this->getComparisonToken() . " " . $this->right . ")";
  }

  abstract protected function getComparisonToken(): string; 
}
