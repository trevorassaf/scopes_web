<?hh // strict

class UpdateUserMethod {

  public function __construct(
    private UpdateByIdQuery<User>  $updateQuery
  ) {}

  public function update(
    ImmMap<string, mixed> $update_params,
    UnsignedInt $id
  ): void {
    try {
      $this->updateQuery
        ->update($update_params, $id)
        ->genWaitHandle()
        ->join();
    } catch (QueryException $ex) {} 
  }
}
