<?hh // strict

class GetStartupDataApiRequestFactory implements RequestFactory<GetStartupDataApiRequest> {

  public function make(
    ImmMap<string, mixed> $raw_field_map
  ): GetStartupDataApiRequest {
    if (!$raw_field_map->isEmpty()) {
      $key = $raw_field_map->firstKey();
      invariant($key !== null, "key can't be null!");

      throw new UnexpectedRequestFieldKeyException(
        __CLASS__,
        $key
      );
    }

    return new GetStartupDataApiRequest();
  }
}
