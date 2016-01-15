<?hh // strict

class GetSessionInfoApiRequestFactory implements RequestFactory<GetSessionInfoApiRequest> {

  public function make(ImmMap<string, mixed> $raw_field_map): GetSessionInfoApiRequest {
    if (!$raw_field_map->isEmpty()) {
      throw new UnexpectedRequestFieldKeyException(__CLASS__, $raw_field_map->keys()[0]);
    }

    return new GetSessionInfoApiRequest();
  }
}
