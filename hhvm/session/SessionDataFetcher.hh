<?hh // strict

interface SessionDataFetcher {

  public function hasSession(): bool;

  public function getSession(): SessionData;
}
