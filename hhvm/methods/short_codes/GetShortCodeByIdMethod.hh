<?hh // strict

class GetShortCodeByIdMethod {

  public function __construct(
    private FetchByIdQuery<ShortCode> $fetchShortCodeByIdQuery
  ) {}

  public function getShortCode(UnsignedInt $short_code_id): ?ShortCode {
    $query_handle = $this->fetchShortCodeByIdQuery->fetch($short_code_id); 
    return $query_handle
      ->getWaitHandle()
      ->join();
  }
}
