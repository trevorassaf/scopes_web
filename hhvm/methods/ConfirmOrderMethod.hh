<?hh // strict

class ConfirmOrderMethod {

  public function __construct(
    private ConfirmedOrderInsertQuery $confirmedOrderInsertQuery
  ) {}

  public function confirm(
    UnsignedInt $id,
    string $title,
    string $description,
    string $short_code,
    string $recording_duration
  ): void {
    try {
    } catch (QueryException $ex) {} 
  }
}
