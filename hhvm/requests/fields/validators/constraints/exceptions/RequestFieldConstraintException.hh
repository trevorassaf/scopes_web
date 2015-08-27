<?hh // strict

class RequestFieldConstraintException extends Exception {

  public function __construct(
    private RequestFieldConstraintType $request
  ) {}
}
