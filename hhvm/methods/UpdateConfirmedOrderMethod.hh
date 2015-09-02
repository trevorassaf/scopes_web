<?hh // strict

class UpdateConfirmedOrderMethod {

  public function __construct(
    private UpdateByIdQuery<ConfirmedOrder>  $updateQuery
  ) {}

  public function update(
    ImmMap<string, mixed> $update_params,
    UnsignedInt $id
  ): void {
    try {
      $this->updateQuery
        ->update($update_params, $id)
        ->getWaitHandle()
        ->join();
    } catch (QueryException $ex) {} 
  }
}
