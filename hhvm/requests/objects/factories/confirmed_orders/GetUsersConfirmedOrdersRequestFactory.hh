<?hh // strict

class GetUsersConfirmedOrdersRequestFactory implements RequestFactory<GetUsersConfirmedOrdersRequest> {

  public function make(
    ImmMap<string, mixed> $raw_field_map
  ): GetUsersConfirmedOrdersRequest {
    if (!$raw_field_map->isEmpty()) {
      $key = $raw_field_map->firstKey();
      invariant($key !== null, "key can't be null!");

      throw new UnexpectedRequestFieldKeyException(
        __CLASS__,
        $key
      );
    }

    return new GetUsersConfirmedOrdersRequest();
  }
}
