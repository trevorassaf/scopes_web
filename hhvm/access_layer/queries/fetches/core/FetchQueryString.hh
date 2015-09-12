<?hh // strict

abstract class FetchQueryString implements FetchQueryMaker {

  public function serialize(): string {
    return $this->getQueryString();
  }

  abstract public function getQueryString(): string;

}
