<?hh // strict

class DeleteShortCodeMethod {

  public function __construct(
    private FetchByIdQuery<ShortCode> $fetchShortCodeByIdQuery,
    private DeleteByIdQuery $deleteShortCodeByIdQuery,
    private ShortCodeTable $shortCodesTable
  ) {}

  public function delete(UnsignedInt $short_code_id): void {
    // Check to make sure short code exists
    $fetch_handle = $this->fetchShortCodeByIdQuery->fetch($short_code_id);

    $short_code = $fetch_handle
      ->getWaitHandle()
      ->join();

    if ($short_code === null) {
      throw new NonextantObjectException();
    }

    // Delete short code 
    $delete_handle = $this->deleteShortCodeByIdQuery->delete(
      $this->shortCodesTable,
      $short_code_id
    ); 

    $delete_handle->getWaitHandle()->join();
  }
}
