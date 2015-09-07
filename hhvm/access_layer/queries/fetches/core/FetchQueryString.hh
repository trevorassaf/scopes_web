<?hh // strict

abstract class FetchQueryString<Tmodel> implements FetchQueryMaker<Tmodel> {

  public function serialize(): string {
    return $this->getQueryString();
  }

  abstract public function getQueryString(): string;

}
