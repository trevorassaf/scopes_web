<?hh // strict

class GetAllUsersRequestFactory implements RequestFactory<GetAllUsersApiRequest> {

  public function make(
    ImmMap<string, mixed> $raw_field_map
  ): GetAllUsersApiRequest {
    if (!$raw_field_map->isEmpty()) {
      $key = $raw_field_map->firstKey();
      invariant($key !== null, "key can't be null!");

      throw new UnexpectedRequestFieldKeyException(
        __CLASS__,
        $key
      );
    }

    return new GetAllUsersApiRequest();
  }
}
